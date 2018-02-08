#!/usr/bin/env nodejs

const static = require('node-static');

const fs = require('fs');
const path = require('path');
const rosnodejs = require('rosnodejs');

rosnodejs.initNode('leobot_web_server').then(() => {
    const nh = rosnodejs.nh;

    console.log('rosnodejs handle: ' + nh);

    nh.getParam('test').then((p) => {
        const port = p;

        console.log('Port parameter: ' + port);
    });
});

const port = 8080; // hard-coded for now
const webContentFolderPath = '../web_content';
const webContentFolderAbsolutePath = path.join(__dirname, webContentFolderPath);
console.log('Starting the web server in folder ' + webContentFolderAbsolutePath);
// This command will fail if path is incorrect
const webContentFolderRealPath = fs.realpathSync(webContentFolderAbsolutePath);

const file = new(static.Server)(webContentFolderRealPath);

require('http').createServer(function (request, response) {
    file.serve(request, response);
}).listen(port);

console.log('Web server started at port ' + port);
