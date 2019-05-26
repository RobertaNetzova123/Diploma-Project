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
    // stderr is sent to stdout of parent process
   // you can set options.stdio if you want it to go elsewhere
    let container1 = execSync('/usr/bin/mosquitto_pub -t server-dispenser -m "cont:1:' + req.query.cont1 + '"');
    let container2 = execSync('/usr/bin/mosquitto_pub -t server-dispenser -m "cont:2:' + req.query.cont2 + '"');
    let container3 = execSync('/usr/bin/mosquitto_pub -t server-dispenser -m "cont:3:' + req.query.cont3 + '"');
    let container4 = execSync('/usr/bin/mosquitto_pub -t server-dispenser -m "cont:4:' + req.query.cont4 + '"');
    let container5 = execSync('/usr/bin/mosquitto_pub -t server-dispenser -m "cont:5:' + req.query.cont5 + '"');
    let container6 = execSync('/usr/bin/mosquitto_pub -t server-dispenser -m "cont:6:' + req.query.cont6 + '"');

    req.flash('success', 'Success');
    res.redirect('back');
  // res.redirect('/');

});
module.exports = router;
