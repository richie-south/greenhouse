import { logsRef } from "../../config/firebase"

export const fetchLogsAction = (payload) => ({
  type: 'FETCH-LOGS',
  payload,
})

export const fetchLogs = () => async dispatch => {
  logsRef.on("value", snapshot => {
    dispatch(fetchLogsAction(snapshot.val()))
  })
}
