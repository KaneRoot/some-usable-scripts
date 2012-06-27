#!/usr/local/bin/perl

use GD;

my $x = 100;
my $y = 15;
my $intersection = $x - 30;
my $espace_entre_mots = 2;
my $w1 = "Alsace";
my $w2 = "Réseau";
my $w3 = "Neutre";

# create a new image
$im = new GD::Image($x,$y);

# allocate some colors
$grey = $im->colorAllocate(140,140,140);
$white = $im->colorAllocate(255,255,255);
$black = $im->colorAllocate(0,0,0);       
$red = $im->colorAllocate(255,0,0);      
$blue = $im->colorAllocate(0,0,255);

# make the background transparent and interlaced
#$im->transparent($white);
$im->interlaced('true');

# Put a black frame around the picture
$im->rectangle(0, 0, $x -1, $y -1, $black);
$im->filledRectangle(1, 1, $x -2, $y -2, $white);
$im->filledRectangle(2, 2, $intersection - $espace_entre_mots, $y -3, $red);

# make sure we are writing to a binary stream
binmode STDOUT;

# Convert the image to PNG and print it on standard output
print $im->png;
