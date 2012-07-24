package MyWrapper;
use GD;
use strict;
use warnings;
use 5.14.2;
use Moo;
use MooX::Options;

has couleurs => ( is => 'ro', builder => '_build_colors' );

option message => ( is => 'rw', 
		doc => 'message', 
		short => 'm',
		format => 's', default => sub { 'message à afficher' } 
	);
option couleur_externe => ( is => 'rw', 
		doc => 'couleur externe', 
		short => 'ce',
		format => 's', default => sub { 'bleu' }
	);
option couleur_interne => ( is => 'rw', 
		doc => 'couleur interne', 
		short => 'ci',
		format => 's', default => sub { 'blanc' }
	);
option couleur_background => ( is => 'rw' , 
		doc => 'couleur du fond (écriture)', 
		short => 'cb',
		format => 's', default => sub { 'noir' }
	);
option taille_x => ( is => 'rw',
		doc => 'taille X', format => 'i',
		short => 'x',
		default => sub { 150 }
	);
option taille_y => ( is => 'rw',
		doc => 'taille Y', format => 'i',
		short => 'y',
		default => sub { 50 }
	);
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
sub afficher_couleurs {
	my ($self) = @_;
	my %couleurs = %{$self->couleurs};
	say "couleurs : " . join( ', ' , keys %couleurs) ;
	while( my ($key , $value) = each %couleurs)
	{
		say "La couleur $key est : " . join(', ' , @$value);
	}
}
sub afficher_valeurs_actuelles {
	my ($self) = @_;
	say "Message : " . $self->message;
	say "couleur_interne : " . $self->couleur_interne;
	say "couleur_externe : " . $self->couleur_externe;
	say "couleur_background : " . $self->couleur_background;
	say "taille_x : " . $self->taille_x;
	say "taille_y : " . $self->taille_y;
}
sub tests {
	my ($self) = @_;
	my %couleurs = %{$self->couleurs};

	say "message : " . $self->message;
	say "couleur_externe : " . $self->couleur_externe;
	say "Cette couleur n'existe pas !" unless exists $couleurs{$self->couleur_externe};
}
sub run {
	my $self = shift;
	#$self->afficher_couleurs ;
	$self->afficher_valeurs_actuelles;
}

1;
