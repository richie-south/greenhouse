import { Store as ReduxStore, applyMiddleware, combineReducers, compose, createStore } from 'redux'
import thunk from 'redux-thunk'
import { logs } from './reducers/logs'

const reducer = combineReducers({
  logs,
})

export const store = createStore(
  reducer,
  compose(
    applyMiddleware(...[thunk]),
  )
)
