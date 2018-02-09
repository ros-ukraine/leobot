#!/usr/bin/env nodejs
'use strict';

const fs = require('fs');
const path = require('path');
const rosnodejs = require('rosnodejs');
const nodeStatic = require('node-static');

function startWebServer(){
    rosnodejs.initNode('leobot_web_server').then(() => {
        const nh = rosnodejs.nh;

        console.log('rosnodejs handle: ' + nh);

        nh.getParam('~port').then((port) => {
            const webContentFolderPath = '../web_content';
            const webContentFolderAbsolutePath = path.join(__dirname, webContentFolderPath);
            console.log('Starting the web server in folder ' + webContentFolderAbsolutePath);
            // This command will fail if path is incorrect
            const webContentFolderRealPath = fs.realpathSync(webContentFolderAbsolutePath);

            const file = new(nodeStatic.Server)(webContentFolderRealPath);

            require('http').createServer(function (request, response) {
                file.serve(request, response);
            }).listen(port);

            console.log('Web server started at port ' + port);
        });
    });
};

// If this module is executed directly rather than included as a library
if (require.main === module) {
    startWebServer();
};
