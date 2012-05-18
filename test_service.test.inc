<?php

function test_service_test_simpletest() {
    $service = GetRefundProposal::create();
    $service->pnr_reference = 'TPWJOD';
    $departure_date = new DateTime();
    $departure_date->setTimeStamp(strtotime('10/05/2012 06:24:00'));
    $arrival_date = new DateTime();
    $arrival_date->setTimeStamp(strtotime('10/05/2012 13:25:00'));
    $journeys[] = new Journey(1, Journey::$TYPE_OUTWARD, 7054660, 8775100, $departure_date, $arrival_date, 7*60+1);
    foreach ($journeys as $journey) {
      $service->addJourney($journey);
    }
    $journeys_response = $service->getJourneys();
    $service->stub = TRUE;
    $service->invoke();
    print_r($service->getFeeRefund());
    print_r($service->getCurrency());
    print_r($service->getGlobalRefundAmount());
    print_r($service->getTotalPenalty());
    print_r($service->getJourneyQuotations());
    
    exit;
    //$this->assertEqual($journeys_response, $journeys, t('Journey set successfully'));
    exit;
}