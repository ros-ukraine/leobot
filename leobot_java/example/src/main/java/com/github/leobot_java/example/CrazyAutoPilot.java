/*
 * Copyright (c) 2019 ROS Ukraine
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *  
 */

package com.github.rosjava.leobot_java.example;

import org.apache.commons.logging.Log;
import org.ros.concurrent.CancellableLoop;
import org.ros.namespace.GraphName;
import org.ros.node.AbstractNodeMain;
import org.ros.node.ConnectedNode;
import org.ros.node.NodeMain;
import org.ros.node.topic.Publisher;

/**
 * A simple CrazyAutoPilot {@link NodeMain}.
 */
public class CrazyAutoPilot extends AbstractNodeMain {

  @Override
  public GraphName getDefaultNodeName() {
    return GraphName.of("rosjava/crazyautopilot");
  }

  @Override
  public void onStart(final ConnectedNode connectedNode) {
    final Publisher<geometry_msgs.Twist> publisher =
        connectedNode.newPublisher("/cmd_vel", geometry_msgs.Twist._TYPE);
    // This CancellableLoop will be canceled automatically when the node shuts
    // down.
    connectedNode.executeCancellableLoop(new CancellableLoop() {

      @Override
      protected void loop() throws InterruptedException {
        final int count = 20;
        final Log log = connectedNode.getLog();        
        geometry_msgs.Twist message = publisher.newMessage();

        log.info("Moving crazy");
        message.getLinear().setX(2.0);
        message.getAngular().setZ(1.0);
        for (int i = 0; i < count; i++) {
          publisher.publish(message);
          Thread.sleep(250);
        }
        
        log.info("Moving crazy backward");
        message.getLinear().setX(-0.2);
        for (int i = 0; i < count; i++) {
          publisher.publish(message);
          Thread.sleep(250);
        }
      }
    });
  }
}
