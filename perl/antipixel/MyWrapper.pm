#!/usr/bin/env perl

package MyWrapper;
use GD;
use strict;
use warnings;
use v5.14;
use Moo;
use MooX::Options;

has qw[couleurs is ro builder _build_colors];

option distance_entre_mots => ( is => 'rw'
	, doc => 'distance en pixels de chaque mot du message'
	, short => 'dem'
	, format => 'i', default => 5
);

option etendu => (is => 'rw'
	, doc => 'si la taille du message est importante, on peut agrandir le cadre à volonté'
	, short => 'ext'
);

option progress_bar => ( is => 'rw'
	, doc => 'si vous souhaitez utiliser le script pour gérer une barre de progression, il faut indiquer un pourcentage'
	, format => 'i', short => 'pb'
);

option debug => ( is => 'rw'
	, doc => 'si vous souhaitez utiliser le script pour gérer une barre de progression'
	, short => 'd'
);

option couleurs_dispo => ( is => 'rw'
	, doc => 'affiche les couleurs disponibles'
	, short => 'cd'
);

option output => ( is => 'rw'
	, doc => 'fichier généré : fichier image (ex: image.png)'
	, short => 'o'
	, format => 's', default => 'image.png'
);

option message => ( is => 'rw'
	, doc => 'message'
	, short => 'm'
	, format => 's', default => 'message à afficher'
);

option couleur_externe => ( is => 'rw'
	, doc => 'couleur externe'
	, short => 'ce'
	, format => 's', default => 'bleu'
);

option couleur_contour => ( is => 'rw'
	, doc => 'couleur contour'
	, short => 'cc'
	, format => 's', default => 'noir'
);

option couleur_interne => ( is => 'rw'
	, doc => 'couleur interne'
	, short => 'ci'
	, format => 's', default => 'rouge'
);

option couleur_background => ( is => 'rw' 
	, doc => 'couleur du fond (écriture)'
	, short => 'cb'
	, format => 's', default => sub { 'noir' }
);

option taille_x => ( is => 'rw'
	, doc => 'taille X', format => 'i'
	, short => 'x'
	, default =>  sub { 150 }
);

option taille_y => ( is => 'rw'
	, doc => 'taille Y', format => 'i'
	, short => 'y'
	, default => sub { 30 }
);

sub _build_colors {
	{
		bleu => [0, 0, 255],
		bleuf => [0, 0, 100],
		rouge => [255, 0, 0],
		rougef => [100, 0, 0],
		vert => [0, 255, 0],
		vertf => [0, 100, 0],
		gris => [150, 150, 150],
		grisf => [100, 100, 100],

		noir => [0, 0, 0],
		blanc => [255, 255, 255]
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
	say "Peut être étendu" if $self->etendu;
	say "Output file : " . $self->output;
	say "Distance entre mots : " . $self->distance_entre_mots;
	say "couleur_interne : " . $self->couleur_interne;
	say "couleur_contour : " . $self->couleur_contour;
	say "couleur_externe : " . $self->couleur_externe;
	say "couleur_background : " . $self->couleur_background;
	say "taille_x : " . $self->taille_x;
	say "taille_y : " . $self->taille_y;
	say "taille_x calculée: " . $self->calcul_taille_x;
}

sub calcul_taille_x {
	my ($self) = @_;
	my $taille_x = $self->taille_x;
	my @mots = split / /, $self->message;
	if( $self->etendu ) {
		$taille_x += 3 * length $_ for( @mots ) ;
	}
	return $taille_x;
}

sub calcul_taille_y {
	my ($self) = @_;
	return $self->taille_y;
}

sub enregistrement_image {
	my ($self, $im) = @_;
# We record the image file
	open (DISPLAY,"> " . $self->output ) || die;
	binmode DISPLAY;
	print DISPLAY $im->png;
	close DISPLAY;
}

sub allocation_des_couleurs {
	my ($self, $im) = @_;

	my %couleurs = %{$self->couleurs};
	my %couleurs_allouees;
# allocate some colors
	while( my ($key , $value) = each %couleurs)
	{
		#say "La couleur $key est : " . join(', ' , @$value);
		$couleurs_allouees{$key} = $im->colorAllocate($$value[0], $$value[1], $$value[2]);
	}
	return %couleurs_allouees ;
}

sub options_sortie_image {
	my ($self, $im) = @_;
# make the background transparent and interlaced
#$im->transparent($couleurs_allouees{'blanc'});
	$im->interlaced('true');
}

sub do_progress_bar{
	my ($self, $im, $couleurs_allouees, $x, $y) = @_;
	my $taille_progress_bar = $self->progress_bar * ($x - 1) / 100;
	my %couleurs_allouees = %$couleurs_allouees;
	$im->filledRectangle(2, 2, $taille_progress_bar, $y -3, $couleurs_allouees{$self->couleur_interne});
}

sub do_antipixel_button {
	my ($self, $im, $couleurs_allouees, $mots, $x, $y) = @_;
	my %couleurs_allouees = %$couleurs_allouees;
	my @mots = @$mots;
	my $current_position = 10;
	for my $i (@mots) {
		$im->filledRectangle($current_position - 3, 2, $current_position + length($i) * 6 + 7, $y - 3, $couleurs_allouees{$self->couleur_interne});
		$im->string(gdMediumBoldFont, $current_position , $y - 0.75 * $y, $i, $couleurs_allouees{'blanc'});
		$current_position += length($i) * 6 + 15;
	}
}

sub do_img {
	my ($self) = @_;
	my @mots = split / /, $self->message;
	my $x = $self->calcul_taille_x;
	my $y = $self->calcul_taille_y;

# create a new image
	my $im = new GD::Image($x,$y);
# allocation des couleurs
	my %couleurs_allouees = $self->allocation_des_couleurs( $im );
# options de sortie de l'image (entrelacée etc.)
	$self->options_sortie_image ( $im );
# début de la construction de l'image à proprement dite
	$im->rectangle(0, 0, $x -1, $y -1, $couleurs_allouees{$self->couleur_contour});
	$im->filledRectangle(1, 1, $x -2, $y -2, $couleurs_allouees{$self->couleur_background});

	$self->do_progress_bar($im,\%couleurs_allouees,$x, $y) if defined $self->progress_bar;
	$self->do_antipixel_button($im, \%couleurs_allouees, \@mots, $x, $y) unless defined $self->progress_bar;

	$self->enregistrement_image( $im );
}

sub mode_debug {
	my ($self) = @_;
	say "ENTER DEBUG MODE";
	$self->afficher_valeurs_actuelles unless $self->couleurs_dispo;
	$self->afficher_couleurs if $self->couleurs_dispo;
}

sub run {
	my ($self) = @_;
	$self->mode_debug if $self->debug;
	$self->do_img unless $self->debug;
}

1;
