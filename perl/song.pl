#!/usr/bin/perl -w
use v5.14;
use Modern::Perl;

my $name = "song";
my $info_perso = "Philippe (karchnu) Pittoli karchnu+travail (at) karchnu.fr";
my $version = "0.1";
my $licence = "GPL3";
my $description = "Permet de savoir quelle est la musique qui tourne.";


weechat::register($name, $info_perso, $version, $licence, $description, "", "");
weechat::print("", "Bonjour, du script perl !");


sub song {
    my ( $data, $buffer, $args ) = @_;

    my @args = split /\s+/, $args;

    my $ip = "portable";
    my $port = "6600";

    $ip = $args[1] if(@args >= 2);
    $port = $args[2] if(@args >= 3);

    my $sortie = `mpc current -p $port -h $ip -f "%title% - %album% : %time%"`;

    weechat::print(weechat::current_buffer(), "[cursong]\t$sortie");
}

weechat::hook_command("song", "description de mon filtre",
    "current [host [port]]",
    "song current [host [port]]",
    "current"
    , "song", "");
