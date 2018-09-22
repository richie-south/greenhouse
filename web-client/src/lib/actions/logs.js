import { logsRef } from "../../config/firebase"

export const fetchLogsAction = (payload) => ({
  type: 'FETCH-LOGS',
  payload,
})


export const fetchLogs = () => async dispatch => {
  logsRef.on("value", snapshot => {
    const values = Object.values(snapshot.val())
    dispatch(fetchLogsAction(snapshot.val()))
  })
}
