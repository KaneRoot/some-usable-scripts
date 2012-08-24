#!/usr/bin/perl

use Modern::Perl;
use AnyEvent;
use AnyEvent::IRC::Client;

my $c = AnyEvent->condvar;
my $cl = AnyEvent::IRC::Client->new;
my $timer;

$cl->reg_cb (connect => sub {
		my ($con, $err) = @_;
		if (defined $err) {
			warn "connect error: $err\n";
			return;
		}
	});

$cl->reg_cb (registered => sub { say "I'm in!"; });
$cl->reg_cb (disconnect => sub { say "I'm out!";  $c->broadcast });

$cl->reg_cb (
	sent => sub {
		my ($con) = @_;

		if ($_[2] eq 'PRIVMSG') {
			print "Sent message!\n";

			$timer = AnyEvent->timer (
				after => 1,
				cb => sub {
					undef $timer;
					say "on est dans cb";
					$con->disconnect ('done')
				}
			);
		}
	}
);

$cl->connect ('irc.geeknode.org', 6667, { nick => '[bot]kanette' });
$cl->send_srv ( PRIVMSG => 'karchnu', 'Bot enabled : woot');
$c->wait;

$cl->disconnect;
