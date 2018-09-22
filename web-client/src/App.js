import React, {Component} from 'react'
import {connect} from 'react-redux'
import {fetchLogs} from './lib/actions/logs'
import {Layout} from 'antd'
import './App.css'
import {TemperatureLine} from './components/temperature'

const {
  Header,
  Sider,
  Content,
  Footer
} = Layout

class App extends Component {

  componentDidMount() {
    console.log('props', this.props)
    this.props.fetchLogs()
  }

  render() {
    return (
      <div className="App">
      <Layout>
        <Header></Header>
        <Content>
          <div style={{ background: '#f0f2f5', padding: '30px' }}>
            <TemperatureLine data={this.props.logs}/>
          </div>

        </Content>
        <Footer>Footer</Footer>
      </Layout>
      </div>
    )
  }
}

const mapStateToProps = (state) => {
  return {
    logs: state.logs
  }
}

const mapDispatchToProps = (dispatch) => {
  return {
    fetchLogs: () => dispatch(fetchLogs())
  }
}

export default connect(mapStateToProps, mapDispatchToProps)(App)
