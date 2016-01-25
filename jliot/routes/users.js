var express = require('express');
var router = express.Router();
var mysql = require('mysql');
/* GET users listing. */
router.get('/', function(req, res, next) {
  res.send('respond with a resource');
});

/* GET users listing. */
router.get('/opendoor/:doorid', function(req, res, next) {
  console.log(req.params.doorid);
  console.log(req.query.rfid);

  var mysqlconn =  mysql.createConnection(global.jliotdbconfig);


     var query = mysqlconn.query('INSERT INTO locklog (rfid,doorid) VALUES (?,?)',[req.query.rfid,req.params.doorid], function(err, result) {
       // Neat!
         if (err) throw err;
         console.log(query.sql);
         console.log(result.insertId);
         //res.send({status:"success"});
     });


    mysqlconn.query('select  field_rfid_value from field_data_field_rfid where field_rfid_value = ?', [req.query.rfid],function(err, rows, fields) {
         if (err) throw err;
         //console.log(rows);
         console.log(rows.length);
        if(rows.length > 0){
           res.send('YES');
        }else{
           res.send('NO');
        }


     });

});



/* GET user locklogs list. */
router.get('/locklogs', function(req, res, next) {

  var mysqlconn =  mysql.createConnection(global.jliotdbconfig);
    mysqlconn.query('SELECT * from locklog order by attime  desc', function(err, rows, fields) {
         if (err) throw err;

         res.render('userlocklogs', { items: rows });


     });

});

module.exports = router;
