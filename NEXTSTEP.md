# Next Steps
##### For specific dates and times.

#### 2018.07.10 Create a JS client for testing

Create a JavaScript client that is served from Texere as a static asset, subscribes to a websocket, and is capable of contacting a REST API when a UI action is taken, getting a response back via REST, but then pumping out a websocket event to every other connected client.

- Make Texere an EventBus subclass, or find another solution
- Crow should import Texere, provide it a string request, and Texere should provide a string response
  - Maybe look at httpxx which is an implementation of http-parser for C, used in Nginx
    - Look into http::Response and http::Request
    - Crow may already have its own copy of this library
  - Perhaps Crow could parse the request, send it to Texere in a custom struct, and Texere could send a custom struct back with its data, which, in turn, are fed through Crow and http-parser?
  - The goal is to embed Texere in places outside of HTTP servers, such as wrapping its logic inside a Node module that can provide a string response in JavaScript
  - Crow doesn't work with streams anyway
    - Even if it did, I could add a stream parser to Texere anyway, and then just forward the stream from Crow
  - Just use basic types provided by std or boost

C++ files that include each other???