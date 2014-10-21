#!/usr/bin/perl -w
use strict;
use warnings;
use v5.14;
use open ':std', ':encoding(UTF-8)';

use HTML::TreeBuilder 5 -weak; # Ensure weak references in use
use WWW::Mechanize;

my $username = '';
my $password = '';

my $rep = "/media/fast/torrents/";
my $url = "https://what.cd/login.php";

my $already_down_album = 0;

mkdir $rep if( not -d $rep);

sub get_torrent {
    my $mech = shift;

    my $c = $mech->content;

    my $ht = HTML::TreeBuilder->new_from_content($c);

    my @elems = $ht->look_down(
        _tag => qr/table/
        , id => 'torrent_details'
    );

    for(@elems) {
        #my @tr = $_->look_down(
        #    _tag => qr/^tr$/
        #);

        #say scalar @tr;

        my @children = $_->content_list();

        # loop on tr tags
        for(@children) {

            # search for a title
            if($_->as_HTML =~ /edition_info/) {

                my @elems = $_->look_down(
                    _tag => qr/strong/
                );

                for(@elems) {
                    say $_->as_trimmed_text(extra_chars => '\xA0');
                }

                $already_down_album = 0;
                next;
            }

            next if $already_down_album;

            # else
            my $txt = $_->as_HTML();

            if($txt =~ m/(Freeleech|Neutral Leech)/i) {

                print "$1 ";

                if($txt =~ m/(FLAC)/i) {
                    if($txt =~ m/(Reported)/i) {
                        say "REPORTED";
                        next ;
                    }

                    my @links = @{  $_->extract_links('a')  };
                    for(@links) {
                        my($link, $element, $attr, $tag) = @$_;
                        if($link =~ /torrents\.php\?action=download&id=[0-9]+&authkey=[0-9a-zA-Z]+&torrent_pass=[0-9a-zA-Z]+/) {

                            my $response = $mech->get($link);

                            if ($response->is_success) {
                                say "FILENAME : ", $response->filename;
                                $mech->save_content( 
                                    "$rep/" . $response->filename
                                    , binmode => ':raw'
                                    , decoded_by_headers => 1 );
                            }
                            else {
                                print STDERR $response->status_line, "\n";
                            }

                            $already_down_album = 1;
                        }
                    }

                }
            }

        }

    }
}


my $mech = WWW::Mechanize->new();
 
$mech->get( $url );

$mech->submit_form(
    form_name => 'login'
    , fields    => { username  => $username, password => $password }
);

my @links = $mech->find_all_links( url_regex => qr/torrents.php\?id=[0-9]+$/ );

for(@links) {
    say $_->url();

    $mech->get($_->url());
    get_torrent $mech;
    $mech->back();
}
