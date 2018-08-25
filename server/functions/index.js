const functions = require('firebase-functions')
const admin = require('firebase-admin')

admin.initializeApp()

exports.createLogEntry = functions.https.onRequest((req, res) => {
  const {
    temprature,
    humidity,
    soilmoisture
  } = req.query

  admin
    .database()
    .ref('logs')
    .push({
      temprature: Number(temprature),
      humidity: Number(humidity),
      soilMoisture: soilmoisture,
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
