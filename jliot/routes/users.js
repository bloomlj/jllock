var express = require('express');
var router = express.Router();

/* GET users listing. */
router.get('/', function(req, res, next) {
  res.send('respond with a resource');
});

/* GET users listing. */
router.get('/opendoor/:doorid', function(req, res, next) {
  console.log(req.params.doorid);
  console.log(req.query.rfid);

  var db = global.jliotdb;

  db.serialize(function() {
    //add log
    // var stmt = db.prepare("INSERT INTO locklog (rfid,doorid) VALUES ('?','?')");
    // stmt.run(req.query.rfid,req.params.doorid);
    // stmt.finalize();
    // console.log("xxx")
     db.run("INSERT INTO locklog (rfid,doorid) VALUES (?,?)",req.query.rfid,req.params.doorid,function(err){
       if(err != null) console.dir(err);
     });

    //  db.run("INSERT INTO locklog (rfid,doorid) VALUES (?,?)","a3b4c109","414",function(err){
    //    if(err != null) console.dir(err);
    //  });

    db.get("SELECT makerid from makers where rfid = ? and role = 'maker' ",req.query.rfid, function(err, row) {
        console.dir(row);
        //console.log(row.id + ": " + row.info);
        if(row ==  undefined){
          res.send('NO');
        }else{
          res.send('YES');
        }
    });

    // var stmt = db.prepare("INSERT INTO makers (makeid,rfid,role) VALUES ('?','?','maker')");
    // stmt.run("bloomlj","a3b4c109");
    // stmt.finalize();
 });
  db.close();


});



/* GET user locklogs list. */
router.get('/locklogs', function(req, res, next) {
  var db = global.jliotdb;
  db.serialize(function() {

    db.all("SELECT * from locklog", function(err, rows) {
        console.dir(rows);
        //console.log(row.id + ": " + row.info);
        res.render('userlocklogs', { items: rows });
    });
 });
  db.close();


});

module.exports = router;
