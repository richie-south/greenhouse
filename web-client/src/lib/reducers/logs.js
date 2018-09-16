
export const logs = (state = [], action) => {
  switch (action.type) {
  case 'FETCH-LOGS':
    return action.payload
  default:
    return state
  }
}
