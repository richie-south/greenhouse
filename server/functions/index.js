const functions = require('firebase-functions')
const admin = require('firebase-admin')

admin.initializeApp()

function stringToBoolean (str) {
  return str === 'true'
}

exports.createLogEntry = functions.https.onRequest((req, res) => {
  const {
    temprature,
    humidity,
    soilmoisture,
    isFanOn,
    isWaterValveOpen,
    isTopHatchOpen,
  } = req.query

  admin
    .database()
    .ref('logs')
    .push({
      temprature: Number(temprature),
      humidity: Number(humidity),
      soilMoisture: soilmoisture,
      wasFanOn: stringToBoolean(isFanOn),
      wasWaterValveOpen: stringToBoolean(isWaterValveOpen),
      wasTopHatchOpen: stringToBoolean(isTopHatchOpen),
      timestamp: new Date().toISOString()
    })
    .then(() =>
      res.json({
        message: 'ok'
      })
    )
    .catch(() => {
      res.json({
        message: 'failed'
      })
    })
})
