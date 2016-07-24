'use strict';

var mongoose = require('mongoose');

mongoose.connect('mongodb://localhost/my_database');

var Schema = mongoose.Schema,
    ObjectId = Schema.ObjectId;

let UserInfo = new Schema({
    p: {type: String},
    n: {type: String},
    a: {type: String},
    i: {type: String},
    o: {type: Date},
    pd: {type: String},
})

let cd = {
  o: {type:String},
  t: {type: Number}, // 0, 1
  s: {type: Date, required: true},
  d: {type: Number, required: true},
  f: {type: Number, required: true},
  _id: false
}
let mcd = {
  m: {type: String, required: true}, // 201607
  i: {type: Boolean, required: true, default: true },
  d: [cd],
  _id: false
};

let CallDetail = new Schema({
    p: {type: String, required: true, unique: true},
    m: [mcd],
});

let userInfo = mongoose.model('UserInfo', UserInfo);
let callDetail = mongoose.model('CallDetail', CallDetail);

function updateUserInfo(p, n, a, i, o, pd) {
    return new Promise((resolve) => {
      if (!p) {
        return resolve(new Error(`wrong parameters`));
      }

      userInfo.findOne({p: p}, (err, record) => {
        if (err) {return resolve(err);}
        if (!record) {
          record = new userInfo({p: p, n: n, a: a, i: i, o: o, pd: pd});
        } else {
          if (n) {record.n = n;}
          if (a) {record.a = a;}
          if (i) {record.i = i;}
          if (o) {record.o = o;}
          if (pd) {record.pd = pd;}
        }
        record.save((err) => {
          if (err) {
            resolve(err);
          } else {
            resolve();
          }
        });
      });
    })
  }

function updateDetails(p, mxxdetails) {
    return new Promise((resolve) => {
        if (!p || !mxxdetails || !(mxxdetails instanceof Map)) {
            return resolve(new Error(`wrong parameters`));
        }

        callDetail.findOne({p: p}, (err, record) => {
            if (err) {return resolve(err);}

            if (!record) {
                let m = [];
                for (let entry of mxxdetails) {
                    m.push({m: entry[0], i: entry[1].i, d: entry[1].data})
                }
                record = new callDetail({p, m});
            } else {
                if (!record.m) {
                    record.m = [];
                }

                for (let entry of mxxdetails) {
                    // 没有次月份数据
                    record.m.push({
                        m: entry[0],
                        i: entry[1].i,
                        d: entry[1].data,
                    });
                }
            }
            record.save((err) => {
                if (err) {
                    resolve(err);
                } else {
                    resolve();
                }
            });
        });
    });
}

let detailsNum = 858;
let mxxdetails = new Map();
let mxxcalldetails = {
    i: true,
    data: []
}
for (let i = 0; i < detailsNum; i++) {
    mxxcalldetails.data.push({
      o: '18510001000',
      t: 0,
      s: new Date(),
      d: 11,
      f: 15
    })
}
mxxdetails.set('201607', mxxcalldetails);

let startPhone = 13800000000;
let phoneNo = 13800000000;
let repeatTimes = 100;
function saveData(){
    let startTime = new Date().getTime();
    updateUserInfo(phoneNo, '张三', '北京市海淀区西三一号院', '370283199901011230', new Date(), 'sfafafafafafdffafdfdafa').then(() => {
        updateDetails(phoneNo, mxxdetails).then(() => {
            console.log(`done and took ${new Date().getTime() - startTime} ms`);
            if (phoneNo < startPhone + repeatTimes) {
                phoneNo++;
                setTimeout(saveData, 0);
            }
        })
    });
}

saveData();
