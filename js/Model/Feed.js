define([
      'Model/FrameRate'
    , 'app.settings'
    , 'underscore'
    , 'backbone'],

    function(FrameRate, settings) {
      var $ = jQuery,
          FeedModel, feed;

      // Holds current feed data (urls to access various feed types -- eg. moving, paused)
      FeedModel = Backbone.Model.extend({
        initialize: function() {
          _.bindAll(this);

          this.on('change:type', this.updateFeed);
          this.on('change:loc', this.updateFeed);
          this.listenTo(FrameRate, 'change:value', this.getFeed);
        },
        defaults: {
          'baseUrl': settings.baseURL
        },
        // update requestAddress with location/view of current selection
        updateFeed: function() {
          this.set({
            'uri': this.get('loc') + '/' + this.get('type'),
            'requestAddr': this.get('baseUrl') + this.get('uri')
          });

          if($.browser.msie && $.browser.version < 10.0) {
            this.ieFeedShim();
          } else {
            this.getFeed();
          }
        },
        ieFeedShim: function() {
          var that = this,
              fr = app.Model.FrameRate.get('value'),
              valFr = 1000;

          if(fr != 0 && fr <= 10) {
            var valFr = (11 - fr) * 1000;
          } else {
            this.set('fullRequest', this.get('requestAddr') + '/jpeg?reset=' + Math.random());
            return 0;
          }
          
          // Refresh image at interval by resetting the fullRequest address with a random number appended to it to trigger change.
          this.intervalId = setInterval(function() {
            if(FrameRate.get('value') != 0) {
              that.set('fullRequest', that.get('requestAddr') + '/jpeg?reset=' + Math.random()); 
            } else {
              clearInterval(that.intervalId);
            }
          }, valFr);
        },
        getFeed: function() {
          if(FrameRate.get('value') == 0) {
            this._pause();
          } else {
            this._play();
          }
        },
        // Begins process of loading jpeg
        _pause: function() {
          this.set('_type','jpeg');
          this.set('fullRequest', this.get('requestAddr') + '/' + this.get('_type'));
        },
        // Begins process of loading mjpeg with framerate from FrameRateModel
        _play: function() {
          this.set('_type','mjpeg' + '/' + FrameRate.get('value'));
          this.set('fullRequest', this.get('requestAddr') + '/' + this.get('_type'));
        },
        updateFramerate: function(f){
          var v = f.get('value');
          if(v > 0) {
            this.render('mjpeg');
            this.playerControls.toggleDisplay('play');
          } else {
            this.render('jpeg');
            this.playerControls.toggleDisplay('pause');
          }
        }
      });

      return {
        initialize: function(){
          feed = new FeedModel();

          this.updateFramerate = feed.updateFramerate;
          this.changeFeed = function(obj) {
            feed.set(obj);
          };
        }
      };

    }
);