var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/on_off', function(req, res) {  
	console.log (req.query);
	console.log(req.query.cont1);
    const { execSync } = require('child_process');


   let prescription = execSync('/usr/bin/mosquitto_pub -t server-dispenser -m "' + JSON.stringify(req.query) + '"');


    req.flash('success', 'Success');
    res.redirect('back');
  // res.redirect('/');

});

module.exports = router;
