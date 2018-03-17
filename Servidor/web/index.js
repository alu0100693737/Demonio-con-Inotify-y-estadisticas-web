var express = require('express')
var app = express()
var path = require('path');

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.use(express.static('public'));

app.get('/', function (req, res) {
  //res.send('Hello World!')
  res.render('index', { title: 'Inotify Estadisticas' });
})

/*
 var router = express.Router();
  module.exports = router;
*/
app.get('/chuchu', function (req, res) {
  //res.send('Hello Chuchu!')
  res.render('index', { title: 'Chuchu' });
})

app.get('/cat', function (req, res) {
  res.send('Got a GET request'+
    '<br/><img src="kitten.jpg" />'
  );
})

app.get('/dog', function (req, res) {
  res.sendFile(path.join(__dirname, 'public/dog.jpg'));
});

var server = app.listen(8080, function () {

  var host = server.address().address
  var port = server.address().port

  console.log('Example app listening at http://%s:%s', host, port)

})