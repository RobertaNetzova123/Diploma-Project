var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

/*GET prescription. */
router.get('/getPrescription', function(req, res) {  
	console.log (req.query);
	
	console.log (req.query.cont1);

	// creating new child process
    const { execSync } = require('child_process');

    let container1 = execSync(
    	'/usr/bin/mosquitto_pub -t dispenser_server -m "cont:1:' +
    	 req.query.cont1 + 
    	 '"');

    let container2 = execSync(
    	'/usr/bin/mosquitto_pub -t dispenser_server -m "cont:2:' +
    	 req.query.cont2 +
    	  '"');

    req.flash('success', 'Success');
    res.redirect('back');
  // res.redirect('/');

});
module.exports = router;

    // stderr is sent to stdout of parent process
   // you can set options.stdio if you want it to go elsewhere