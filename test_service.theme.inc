<?php
/**
 * Themes a module status display.
 */
function theme_test_service_storage_link($vars) {
  $classes = array(
    TEST_SERVICE_RUNNING => 'admin-default',
    TEST_SERVICE_FAILING => 'admin-overridden',
    TEST_SERVICE_CHECKING => 'admin-loading',
    TEST_SERVICE_RELOAD => 'admin-reload',
  );
  $default_text = array(
    TEST_SERVICE_RUNNING => t('Running'),
    TEST_SERVICE_FAILING => t('Failing'),
    TEST_SERVICE_CHECKING => t('Checking...'),
    TEST_SERVICE_RELOAD => 'R',
    );
  $text = isset($vars['text']) ? $vars['text'] : $default_text[$vars['storage']];
  if ($vars['path']) {
    $vars['options']['attributes']['class'][] = $classes[$vars['storage']];
    $vars['options']['attributes']['class'][] = 'features-storage';
    return l($text, $vars['path'], $vars['options']);
  }
  else {
    return "<span class='{$classes[$vars['storage']]} features-storage'>{$text}</span>";
  }
}
/**
 * Theme for management form.
 */
function theme_test_service_form_package(&$vars) {
  // reusing feature css.
  drupal_add_css(drupal_get_path('module', 'test_service') . '/test_service.css');
  drupal_add_js(drupal_get_path('module', 'test_service') . '/test_service.js');

  $output = '';

  $header = array(t('Service'), t('Message'), );
  if (isset($vars['form']['state'])) {
    $header[] = t('Status');
  }

  $rows = array();
  foreach (element_children($vars['form']['status']) as $element) {
    // Yank title & description fields off the form element for
    // rendering in their own cells.
    $row = array();
    $row['name'] = array('data' => drupal_render($vars['form']['status'][$element]), 'class' => 'name');
    $row['status'] = array('data' => t('Fetching....'), 'class' => array('status'));
    //array('data' => drupal_render($vars['form']['status'][$element]), 'class' => array('status'));
    // $row['sign'] = array('data' => drupal_render($vars['form']['sign'][$element]), 'class' => array('sign'));

    if (isset($vars['form']['state'])) {
      $row['state'] = array('data' => drupal_render($vars['form']['state'][$element]), 'class' => array('state'));
    }
    if (isset($vars['form']['actions'])) {
      $row['actions'] = array('data' => drupal_render($vars['form']['actions'][$element]), 'class' => array('actions'));
    }
    $rows[] = array('data' => $row);
  }

  if (empty($rows)) {
    $rows[] = array('', array('data' => t('No features available.'), 'colspan' => count($header)));
  }

  $class = count($header) > 3 ? 'features features-admin' : 'features features-manage';
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'features-form-table', 'class' => array($class))));

  // Prevent section from being rendered by drupal_render().

  $output .= drupal_render($vars['form']['buttons']);
  $output .= drupal_render_children($vars['form']);
  return $output;
}