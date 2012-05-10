<?php
/**
 * @file
 *   Admin related functionalities
 * 
 */
/**
 * 
 */
function test_service_status($service) {
  $fn = 'test_service_'.str_replace('-', '_', $service);
  $default = array('status' => 2, 'message' => 'Your service not configured proper in service manager!!!');
  $result = array('status' => 2, 'message' => 'Your service not added to service manager yet...');
  if (function_exists($fn)) {
    try {
      $result = $fn();
    }
    catch (Exception $e) {
      $result = array('status' => 2, 'message' => t('Exception:%message', array('%message' => $e->getMessage())));
    }
  }
  if (!is_array($result)) {
    $result = $default;
  }else {
    $result += $default;
  }

  // return drupal_json_output($fn());
  return drupal_json_output($result);
}

/**
 * admin page callback.
 */
function test_service_admin_form($form, $form_state) {
  $services = test_service_get_all_services();
  foreach ($services as $name => $service) {
    $package = $service->export_module;
    // Set up package elements
    if (!isset($form[$package])) {
      $form[$package] = array(
        '#tree' => FALSE,
        '#title' => $package,
        '#theme' => 'test_service_form_package',
        '#type' => 'fieldset',
        '#group' => 'packages',
      );
      $form[$package]['links'] =
      $form[$package]['version'] =
      $form[$package]['weight'] =
      $form[$package]['status'] =
      $form[$package]['action'] = array('#tree' => TRUE);
    }
    $form[$package]['status'][$name] = array(
      '#type' => 'item',
      '#title' => $service->machine_name,
      '#description' => $service->description,
    );
    $href = '';
    $state = theme('test_service_storage_link', array('storage' => TEST_SERVICE_CHECKING, 'path' => $href));
    $state .= l(t('Check'), "admin/structure/test-service/{$name}/status", array('attributes' => array('class' => array('admin-check'))));
    $state .= theme('test_service_storage_link', array('storage' => TEST_SERVICE_RUNNING, 'path' => $href));
    $state .= theme('test_service_storage_link', array('storage' => TEST_SERVICE_FAILING, 'path' =>  $href));
    
    $form[$package]['state'][$name] = array(
      '#markup' => $state,
    );
  }
  ksort($form);
  $form = array('packages' => array('#type' => 'vertical_tabs')) + $form;
  return $form;
}

function test_service_get_all_services() {
  return messagequeue_service_load_all();
  //return messagequeue_service_load('get_od_pair');
}