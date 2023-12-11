package com.example.art

import android.graphics.Color
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.github.mikephil.charting.charts.BarChart
import com.github.mikephil.charting.data.BarData
import com.github.mikephil.charting.data.BarDataSet
import com.github.mikephil.charting.data.BarEntry
import com.github.mikephil.charting.formatter.ValueFormatter
import com.github.mikephil.charting.formatter.IndexAxisValueFormatter

class MainActivity2 : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main2)

        // 첫 번째 액티비티로부터 데이터를 받기 위한 부분
        val receivedData1 = intent.getFloatExtra("m", 0.0f)
        val receivedData2 = intent.getFloatExtra("g", 0.0f)
        val receivedData3 = intent.getFloatExtra("p", 0.0f)

        // receivedData1, receivedData2, receivedData3가 0이 아닌 경우에만 업데이트하는 조건 추가
        if (receivedData1 != 0.0f || receivedData2 != 0.0f || receivedData3 != 0.0f) {
            updateChartData(receivedData1, receivedData2, receivedData3)
        }
    }

    private fun updateChartData(receivedData1: Float, receivedData2: Float, receivedData3: Float) {
        val barChart: BarChart = findViewById(R.id.barChart)

        val entries1 = arrayListOf<BarEntry>()
        entries1.add(BarEntry(0f, receivedData1 * 4))
        entries1.add(BarEntry(1f, 0f))
        entries1.add(BarEntry(2f, 0f))

        val entries2 = arrayListOf<BarEntry>()
        entries2.add(BarEntry(0f, 0f))
        entries2.add(BarEntry(1f, receivedData2 * 4))
        entries2.add(BarEntry(2f, 0f))

        val entries3 = arrayListOf<BarEntry>()
        entries3.add(BarEntry(0f, 0f))
        entries3.add(BarEntry(1f, 0f))
        entries3.add(BarEntry(2f, receivedData3 * 4))

        val barDataSet1 = BarDataSet(entries1, "")
        val barDataSet2 = BarDataSet(entries2, "")
        val barDataSet3 = BarDataSet(entries3, "")

        barDataSet1.color = Color.rgb(50, 60, 47) // metal
        barDataSet2.color = Color.rgb(50, 60, 47) // glass
        barDataSet3.color = Color.rgb(50, 60, 47) // plastic

        val barData = BarData(barDataSet1, barDataSet2, barDataSet3)

        // 값 텍스트 크기 조절
        barDataSet1.setValueTextSize(15f)
        barDataSet2.setValueTextSize(15f)
        barDataSet3.setValueTextSize(15f)

        barChart.description.isEnabled = false // Description 비활성화

        barChart.data = barData

        // x축의 라벨 숨기기
        barChart.xAxis.isEnabled = false

        // 왼쪽 축의 라벨 숨기기
        barChart.axisLeft.isEnabled = false

        // 오른쪽 축의 라벨 숨기기
        barChart.axisRight.isEnabled = false

        barChart.setDrawGridBackground(false) // 바차트의 배경 격자 무늬 없애기

        barChart.legend.isEnabled = false // 범례(legend) 비활성화

        // 선택적으로 추가적인 설정 가능
        barChart.setFitBars(true) // 막대 사이 간격 조정
        barChart.invalidate() // 그래프 업데이트

        // x 축의 값 표시 간격 설정
        barChart.xAxis.valueFormatter = IndexAxisValueFormatter(arrayOf("", "", ""))

        // 막대 아래에 값 표시 설정
        barDataSet1.setDrawValues(true)
        barDataSet2.setDrawValues(true)
        barDataSet3.setDrawValues(true)

        barChart.axisLeft.valueFormatter = object : ValueFormatter() {
            override fun getFormattedValue(value: Float): String {
                return if (value == 0f) "" else value.toInt().toString()
            }
        }
    }
}