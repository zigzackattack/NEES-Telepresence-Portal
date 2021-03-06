NEES Telepresence Portal
========================

A portal for streaming and controlling live AXIS webcam feeds from UCSB NEES sites. It can be used for any flexTPS based API and modified to work directly with the AXIS 213 PTX API.

Features
--------
* Pan, tilt, zoom, focus, center and more.
* Download screenshots in bulk.
* Location bookmarking.
* Drupal Administrative interface.
* Camera position indicators.
* Clean KendoUI/Bootstrap based flat design.
* Responsive.
* Accessible as Drupal page or independently as static html file.

Installation
------------
You can quickly and easily install the NEES Telepresence Portal by cloning the repo and running the following commands from the root of the cloned directory.

```
npm install
```
```
grunt install
```

When prompted, enter the Drupal database settings

```
grunt setEnv
```

If you want to use the telepresence app using RequireJS's Asynchronous Module Definition pattern use `dev`, otherwise use `live` to use the compressed and optimized version.

Requirements
------------
* Telepresence Proxy Server and AXIS 213 TPZ webcam.
* Drupal 7.x
* Node.js
* Bower

Languages
---------

The NEES Telepresence module is written in Javascript (using the Backbone, Underscore, Requrejs and jQuery libraries), node.js and PHP using the Drupal CMS framework.

Organization/Code
------------

The majority of the markup exists in the telepresence.tpl.php file. Some markup is inserted by javascript.

Javascript templates can be found in public/js/Template/

The front end app is organized in a model-view-* (Router, or Collection) pattern.

public/js/View -- Objects related to rendering and controlling elements in the DOM.
public/js/Router -- Contains the one Router.js file used to control the state of the application.
public/js/Collection -- Files organizing models into Backbone Collections.
public/js/Model -- the Core Model used in the application (Camera.js).

public/components contains vendor files required by the app. You should install these by running ```bower install``` from the 'public' directory.

The front end application compiles the necessary files using Requirejs, an asynchronous module loading library. You can read the documentation for that at http://requirejs.org/.

Technology
----------

###Socket.io
To keep the camera position up to date in the browser, the node.js server employs a back end library called socket.io to push events to the client when the camera shifts positions. For browsers that don't support websockets, socket.io has several fallbacks such as long polling.

Todo
----

- [ ] remove all extra css
- [ ] find a better way to keep focus/iris sliders in sync after autofocus/autoiris
- [ ] make global Telepresence variable a module.

More Information
----------------

* [http://www.backbonejs.org Backbone]
* [http://www.underscorejs.org Underscore]
* [http://fgnass.github.com/spin.js/ Spin.js]
