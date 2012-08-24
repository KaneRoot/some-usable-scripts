#!/usr/bin/perl

use Modern::Perl;
use AnyEvent;
use AnyEvent::IRC::Client;

my $c = AnyEvent->condvar;
my $cl = AnyEvent::IRC::Client->new;
$cl->reg_cb (connect => sub {
		my ($con, $err) = @_;
		if (defined $err) {
			warn "connect error: $err\n";
			return;
		}
	});
$cl->connect ('irc.geeknode.org', 6667, { nick => '[bot]kanette' });
$cl->send_srv ( PRIVMSG => 'karchnu', 'Hi there!');
$c->wait;

$cl->disconnect;
