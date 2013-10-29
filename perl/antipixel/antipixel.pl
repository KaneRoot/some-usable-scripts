#!/usr/bin/env perl 
use strict;
use warnings;
use MyWrapper;
my $wrapper = MyWrapper->new_with_options();
#$wrapper->afficher_valeurs_actuelles;
$wrapper->run();
