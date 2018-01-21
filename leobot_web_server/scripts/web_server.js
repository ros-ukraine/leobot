#!/usr/bin/env nodejs

const static = require('node-static');

const fs = require('fs');
const path = require('path')

const port = 80;
const webContentFolderPath = '../../docs/design/management/Leobot_html';
const webContentFolderAbsolutePath = path.join(__dirname, webContentFolderPath);
console.log('Starting the web server in folder ' + webContentFolderAbsolutePath);
// This command will fail if path is incorrect
const webContentFolderRealPath = fs.realpathSync(webContentFolderAbsolutePath);

const file = new(static.Server)(webContentFolderRealPath);

require('http').createServer(function (request, response) {
    file.serve(request, response);
}).listen(port);

console.log('Web server started at port ' + port);