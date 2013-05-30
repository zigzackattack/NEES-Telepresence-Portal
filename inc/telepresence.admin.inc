<?php
/**
 * @file
 * Administrative functions for telepresence app.
 */

/**
 * Generates form for general telepresence settings
 */
function telepresence_config() {
	$form = array();
	$api  = variable_get('telepresence_api', '');

	$form['telepresence_about'] = array(
		'#title' => t('About'),
		'#type' => 'text_format',
		'#default_value' => telepresence_get_settings()
	);
	$form['telepresence_api'] = array(
		'#type' => 'textfield',
		'#title' => t('FlexTPS API URL'),
		'#description' => t('(eg. http://tpm.nees.ucsb.edu/feeds/).'),
		'#default_value' => $api
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'save',
		'#submit' => array('telepresence_save_settings')
	);
	return($form);
}

/**
 * Generates form for managing cameras.
 */
function telepresence_camera_form() {
	$form = array();

	$form['site_name'] = array(
		'#title' => t('Site Name'),
		'#description' => t('full name of site'),
		'#type' => 'textfield',
		);

	$form['site_safe_name'] = array(
		'#title' => t('Site Safe Name'),
		'#description' => t('(eg. gvda or wla).'),
		'#type' => 'textfield'
		);

	$form['camera_name'] = array(
		'#title' => t('Camera Name'),
		'#description' => t('eg. Full-Size or Inside'),
		'#type' => 'textfield',
		);

	$form['camera_safe_name'] = array(
		'#title' => t('Camera Safe Name'),
		'#description' => t('eg. internal'),
		'#type' => 'textfield',
		);

	$form['home'] = array(
		'#title' => 'Default Values',
		'#type' => 'fieldset'
		);

	$form['home']['value_pan'] = array(
		'#type' => 'textfield',
		'#title' => 'Home Pan',
		'#description' => 'Default pan to location (from 0 - 100).'
		);

	$form['home']['value_tilt'] = array(
		'#type' => 'textfield',
		'#title' => 'Home Tilt',
		'#description' => 'Default tilt to location (from 0 - 100).'
		);

	$form['home']['value_zoom'] = array(
		'#type' => 'textfield',
		'#title' => 'Default Zoom',
		'#description' => 'Default pan to location (from 0 - 20).'
		);

	$form['home']['value_focus'] = array(
		'#type' => 'textfield',
		'#title' => 'Default Focus',
		'#description' => 'Default pan to location (from 0 - 20).'
		);

	$form['id'] = array(
		'#type' => 'hidden',
		'#default_value' => null
		);

	$form['submit'] = array(
		'#type' => 'submit',
		'#submit' => array('telepresence_create_camera'),
		'#value' => 'Add'
		);

	return $form;
}

/**
 * Generates page for managing cameras (includes camera form and camera table).
 */
function telepresence_add_camera() {
	$page = "";

	$t_head = array('id', 'site name','site safe name','camera name','camera safe name', 'pan value', 'tilt value', 'zoom value', 'focus value', 'admin');

	$rows = telepresence_find_camera();

	foreach($rows as $key=>$row) {
		foreach($row as $colkey=>$item) {
			$new = array('data' => $item, 'class' => $colkey);
			$rows[$key]['data'][] = $new;
		}
		$rows[$key] = $rows[$key]['data'];
		$rows[$key]['edit'] = '<input type="submit" class="form-submit camera-edit" name="site" value="Edit" /><input type="submit" class="form-submit camera-delete" name="site" value="Delete" />';
	}

	if($rows) {
		$page = theme('table', array('header' => $t_head, 'rows' => $rows));
	}

	$page .= drupal_render(drupal_get_form('telepresence_camera_form'));

	drupal_add_library('system', 'ui.autocomplete');

	drupal_add_js(drupal_get_path('module', 'telepresence') . '/js/Admin/module.js');

	drupal_add_js(drupal_get_path('module', 'telepresence') . '/js/Admin/CameraManager.js');

	return $page;
}

/**
 * Submit handler for telepresence camera manager -- creates camera.
 */
function telepresence_create_camera($form, &$form_state) {
	$input = $form_state['input'];

	$id = ($input['id'] == '') ? null : $input['id'];

	telepresence_save_camera($id, $input);
}

/**
 * Saves settings from telepresence_config().
 */
function telepresence_save_settings($form, &$form_state) {
	try {
		variable_set('telepresence_api', $form_state['input']['telepresence_api']);

		db_truncate('telepresence')->execute();

		db_insert('telepresence')
		->fields(array(
			'about' => $form_state['input']['telepresence_about']['value'])
		)
		->execute();
	} catch (Exception $e) {
		dsm($e);
	}
}
/**
 * Retrieves current settings from database for easily setting form defaults
 */
function telepresence_get_settings() {
	$r = db_select('telepresence', 't')
		->fields('t')
		->execute()
		->fetchAssoc();
	return $r['about'];
}