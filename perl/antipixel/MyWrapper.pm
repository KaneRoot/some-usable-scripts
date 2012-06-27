package MyWrapper;
use GD;
use strict;
use warnings;
use 5.16.0;
use Moo;
use MooX::Options;

has couleurs => ( is => 'ro', builder => '_build_colors' );


option mess => ( is => 'rw', 
		doc => 'message', format => 's', default => sub { 'message à afficher' } );
option couleur_externe => ( is => 'rw', 
		doc => 'couleur externe', format => 's', default => sub { 'bleu' });
option couleur_interne => ( is => 'rw', 
		doc => 'couleur interne', format => 's' );
option couleur_background => ( is => 'rw' , 
		doc => 'couleur du fond (écriture)', format => 's');


sub _build_colors {
	{
		bleu => [0, 0, 255],
		rouge => [255, 0, 0],
		vert => [0, 255, 0],
		noir => [0, 0, 0],
		blanc => [255, 255, 255],
		gris => [140, 140, 140]
	};
}
sub tests {
	my ($self) = @_;
	my %couleurs = %{$self->couleurs};

	say "mess : " . $self->mess;
	say "couleur_externe : " . $self->couleur_externe;
	say "Cette couleur n'existe pas !" unless exists $couleurs{$self->couleur_externe};
	say "couleurs : " . join( ', ' , keys %couleurs) ;
	while( my ($key , $value) = each %couleurs)
	{
		say "La couleur $key est : " . join(', ' , @$value);
	}
#	say "couleur_interne : " . $self->couleur_interne;
#	say "couleur_background : " . $self->couleur_background;
}
sub run {
	my $self = shift;
	say "RUN !!!";
}

1;
