#!/usr/bin/perl -w
use strict;
use WWW::Mechanize;

my $nom = "";
my $pass = "";
my @fields = q/connexion_password/;
my $url = "http://millenium-servers.com/index.php";

my $m = WWW::Mechanize->new(
		stack_depth => 5,
		);
$m->get($url);
# Afficher l'ensemble des formulaires 
# print $_->dump for $m->forms();
$m->form_with_fields( @fields );
$m->set_fields(
		connexion_active => "yes",
		connexion_username => $nom,
		connexion_password => $pass,
#		connexion_save_connexion => "false"
		);
$m->submit();
# Connaître le lien sur lequel on est actuellement
print($m->uri."\n");
# $m->reload();
# knowyourmeme
$m->get("http://millenium-servers.com/voter.php");
#my $link = $m->find_link(
#		text => "voter.php"
#text_regex => qr/www\.rpg\.paradise\.com\.\*vote=\.\*/i
#		);
$m->follow_link(text => 'http://www.rpg-paradize.com/?page=vote&vote=5846');
#print($m->uri."\n");
#$m->back();
print($m->uri."\n");
#print $m->content() ;

# Afficher un lien
#print($link->url . "\n");
