package com.example.art

import android.Manifest
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import android.widget.Button
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import java.io.IOException
import java.io.InputStream
import java.util.UUID
import android.app.AlertDialog

interface BluetoothDataListener {
    fun onDataReceived(m: Float, g: Float, p: Float)
}

class MainActivity : AppCompatActivity(), BluetoothDataListener {

    private var bluetoothAdapter: BluetoothAdapter? = null
    private val REQUEST_ENABLE_BT = 1
    private val REQUEST_LOCATION_PERMISSION = 2
    private val REQUEST_BLUETOOTH_ADMIN_PERMISSION = 3
    private var isButtonClicked = false
    private var bluetoothDataListener: BluetoothDataListener? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val bluetoothManager = getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        bluetoothAdapter = bluetoothManager.adapter

        val connectButton: Button = findViewById(R.id.connectButton)
        connectButton.setOnClickListener {
            if (!isButtonClicked) {
                checkBluetoothPermission()
            } else {
                val intent = Intent(this@MainActivity, MainActivity2::class.java)
                startActivity(intent)
            }
        }

        bluetoothDataListener = object : BluetoothDataListener {
            override fun onDataReceived(m: Float, g: Float, p: Float) {
                val intent = Intent(this@MainActivity, MainActivity2::class.java)
                intent.putExtra("m", m)
                intent.putExtra("g", g)
                intent.putExtra("p", p)
                startActivity(intent)
            }
        }

        // Bluetooth 데이터 리스너 설정
        val dataListener: BluetoothDataListener = object : BluetoothDataListener {
            override fun onDataReceived(m: Float, g: Float, p: Float) {
                // 데이터를 받았을 때의 동작을 정의합니다.
                println("Received Data: m=$m, g=$g, p=$p")

                // MainActivity2로 데이터를 전달하는 등의 작업을 수행할 수 있습니다.
                val intent = Intent(this@MainActivity, MainActivity2::class.java)
                intent.putExtra("m", m)
                intent.putExtra("g", g)
                intent.putExtra("p", p)
                startActivity(intent)
            }
        }
        setBluetoothDataListener(dataListener)
    }

    private fun checkBluetoothPermission() {
        if (bluetoothAdapter == null) {
            Toast.makeText(this, "블루투스를 지원하지 않는 기기입니다.", Toast.LENGTH_SHORT).show()
            return
        }

        if (!bluetoothAdapter!!.isEnabled) {
            val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT)
        } else {
            checkLocationPermission()
        }
    }

    private fun checkLocationPermission() {
        if (ContextCompat.checkSelfPermission(
                this,
                Manifest.permission.ACCESS_FINE_LOCATION
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.ACCESS_FINE_LOCATION),
                REQUEST_LOCATION_PERMISSION
            )
        } else {
            checkBluetoothAdminPermission()
        }
    }

    private fun checkBluetoothAdminPermission() {
        if (ContextCompat.checkSelfPermission(
                this,
                Manifest.permission.BLUETOOTH_ADMIN
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.BLUETOOTH_ADMIN),
                REQUEST_BLUETOOTH_ADMIN_PERMISSION
            )
        } else {
            showBluetoothDevicesDialog()
        }
    }

    private fun showBluetoothDevicesDialog() {
        val pairedDevices = bluetoothAdapter?.bondedDevices
        val deviceList: MutableList<BluetoothDevice> = mutableListOf()
        val deviceNames: MutableList<String> = mutableListOf()

        pairedDevices?.forEach { device ->
            deviceList.add(device)
            deviceNames.add("${device.name}\n${device.address}")
        }

        val dialogBuilder = AlertDialog.Builder(this)
        dialogBuilder.setTitle("연결할 기기를 선택하세요.")
        dialogBuilder.setItems(deviceNames.toTypedArray()) { _, which ->
            val selectedDevice = deviceList[which]

            if (ContextCompat.checkSelfPermission(
                    this,
                    Manifest.permission.BLUETOOTH_ADMIN
                ) != PackageManager.PERMISSION_GRANTED
            ) {
                ActivityCompat.requestPermissions(
                    this,
                    arrayOf(Manifest.permission.BLUETOOTH_ADMIN),
                    REQUEST_BLUETOOTH_ADMIN_PERMISSION
                )
                return@setItems
            }

            establishConnection(selectedDevice)
        }
        dialogBuilder.setNegativeButton("취소") { dialog, _ ->
            dialog.dismiss()
        }

        val dialog = dialogBuilder.create()
        dialog.show()
    }

    private var bluetoothSocket: BluetoothSocket? = null

    private fun establishConnection(device: BluetoothDevice) {
        if (ContextCompat.checkSelfPermission(
                this,
                Manifest.permission.BLUETOOTH_ADMIN
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.BLUETOOTH_ADMIN),
                REQUEST_BLUETOOTH_ADMIN_PERMISSION
            )
            return
        }


        val MY_UUID: UUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb")

        try {
            bluetoothSocket = device.createRfcommSocketToServiceRecord(MY_UUID)
            bluetoothSocket?.connect()
            Toast.makeText(this, "연결 되었습니다.", Toast.LENGTH_SHORT).show()
            bluetoothSocket?.let { startDataReceivingThread(it) } // Safe call using let
            isButtonClicked = true
            val connectButton: Button = findViewById(R.id.connectButton)
            connectButton.text = "CHECK!"
        } catch (e: IOException) {
            e.printStackTrace()
            Toast.makeText(this, "연결 실패하였습니다.", Toast.LENGTH_SHORT).show()
        }
    }

    private fun startDataReceivingThread(socket: BluetoothSocket) {
        val inputStream: InputStream = socket.inputStream
        val buffer = ByteArray(1024)
        var bytes: Int

        Thread {
            try {
                while (true) {
                    bytes = inputStream.read(buffer)
                    if (bytes > 0) {
                        val data = buffer.copyOfRange(0, bytes)
                        parseReceivedData(data)
                    }
                }
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }.start()
    }

    // Bluetooth 데이터를 파싱하고 리스너를 통해 MainActivity로 전달
    private fun parseReceivedData(data: ByteArray) {
        val receivedString = data.toString(Charsets.UTF_8)
        val values = receivedString.split(",")

        if (values.size == 3) {
            val m = values[0].toFloat()
            val g = values[1].toFloat()
            val p = values[2].toFloat()

            // 데이터가 수신되면 리스너를 통해 MainActivity로 전달
            bluetoothDataListener!!.onDataReceived(m, g, p)
        }
    }

    fun setBluetoothDataListener(listener: BluetoothDataListener) {
        bluetoothDataListener = listener
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        when (requestCode) {
            REQUEST_BLUETOOTH_ADMIN_PERMISSION -> {
                if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    showBluetoothDevicesDialog()
                } else {
                    Toast.makeText(this, "블루투스 권한이 필요합니다.", Toast.LENGTH_SHORT).show()
                }
            }

            else -> super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        }
    }

    override fun onDestroy() {
        super.onDestroy()
    }

    override fun onDataReceived(m: Float, g: Float, p: Float) {
        // 데이터를 받았을 때의 동작을 정의합니다. 예를 들어, 받은 데이터를 출력하거나 다른 작업을 수행할 수 있습니다.
        println("Received Data: m=$m, g=$g, p=$p")

        // MainActivity2로 데이터를 전달하는 등의 작업을 수행할 수 있습니다.
        val intent = Intent(this@MainActivity, MainActivity2::class.java)
        intent.putExtra("m", m)
        intent.putExtra("g", g)
        intent.putExtra("p", p)
        startActivity(intent)
    }

}