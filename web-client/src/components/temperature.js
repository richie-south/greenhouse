import React, {Component} from 'react'
import * as V from 'victory'
import {VictoryChart, VictoryLine, VictoryAxis, VictoryLabel, VictoryTheme, VictoryTooltip} from 'victory'
import styled from 'styled-components'
import {Card, Icon} from 'antd'

const Title = styled.h3`
  padding-left: 20px;
`

const {Meta} = Card

export class TemperatureLine extends Component {
  render() {
    console.log(Object.values(this.props.data))
    const data2 = Object.values(this.props.data).map(
      ({timestamp, temprature}) => ({
        x: new Date(timestamp),
        y: temprature
      })
    )
    const data = data2.slice(Math.max(data2.length - 96, 1))
    const loading = data.length === 0;
    return (
        <Card
          loading={loading}
          actions={[<Icon type="left-circle" theme="twoTone" />, <Icon type="right-circle" theme="twoTone" />, <Icon type="clock-circle" theme="twoTone" />]}
        >

        <Meta
          title="temperature"
          description="24h"
        />
          <VictoryChart
          theme={VictoryTheme.material}
          width={600}
        >
          <VictoryAxis/>
          <VictoryAxis dependentAxis/>
          <VictoryLine

            style={{
              data: { stroke: "#f5222d" },
            }}
            data={data}
          />
        </VictoryChart>
        </Card>
    )
  }
}
