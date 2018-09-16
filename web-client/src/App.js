import React, {Component} from 'react'
import {connect} from 'react-redux'
import {fetchLogs} from './lib/actions/logs'

class App extends Component {

  componentDidMount() {
    console.log('props', this.props)
    this.props.fetchLogs()
  }

  render() {
    return (
      <div className="App">
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
