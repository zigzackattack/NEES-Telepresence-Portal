define(['underscore'
	, 'backbone'
	, 'domReady'], 

	function($) {
	'use strict'

	var InfoView, info;

	InfoView = Backbone.View.extend({
		tagName: 'article',
		id: 'info-view',
		initialize: function() {
			_.bindAll(this);
		},
		render: function() {
			var $parent = $('#telepresence-dashboard'),
				txt = Drupal.settings.telepresence_about;

			this.$el.html(txt);
			$parent.html(this.$el);
		}
	});

	info = new InfoView()

	return {
		show: function() {
			info.$el.show();
		},
		hide: function() {
			info.$el.hide();
		},
		render: info.render
	}
}(jQuery));