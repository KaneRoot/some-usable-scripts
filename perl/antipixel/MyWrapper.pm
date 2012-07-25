package MyWrapper;
use GD;
use strict;
use warnings;
use 5.14.2;
use Moo;
use MooX::Options;

has couleurs => ( is => 'ro', builder => '_build_colors' );

option distance_entre_mots => ( is => 'rw',
		doc => 'distance en pixels de chaque mot du message',
		short => 'dem',
		format => 'i', default => sub { 5 }
	);
option output => ( is => 'rw',
		doc => 'fichier généré : fichier image (ex: image.png)',
		short => 'o',
		format => 's', default => sub { 'image.png' }
	);
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
option couleur_contour => ( is => 'rw', 
		doc => 'couleur contour', 
		short => 'cc',
		format => 's', default => sub { 'noir' }
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
	say "Distance entre mots : " . $self->distance_entre_mots;
	say "couleur_interne : " . $self->couleur_interne;
	say "couleur_externe : " . $self->couleur_externe;
	say "couleur_background : " . $self->couleur_background;
	say "taille_x : " . $self->taille_x;
	say "taille_y : " . $self->taille_y;
}
sub tests {
	my ($self) = @_;
	my %couleurs = %{$self->couleurs};

	say "couleur_externe : " . $self->couleur_externe;
	say "Cette couleur n'existe pas !" unless exists $couleurs{$self->couleur_externe};
}
sub run {
	my $self = shift;
	#$self->afficher_couleurs ;
	#$self->afficher_valeurs_actuelles;
	my %couleurs = %{$self->couleurs};
	my %couleurs_allouee;

	my @mots = split / /, $self->message;
	my $x = $self->taille_x;
	my $y = $self->taille_y;
	my $intersection = $x - 30;

# create a new image
	my $im = new GD::Image($x,$y);

# allocate some colors
	while( my ($key , $value) = each %couleurs)
	{
		#say "La couleur $key est : " . join(', ' , @$value);
		$couleurs_allouee{$key} = $im->colorAllocate($$value[0], $$value[1], $$value[2]);
	}
# make the background transparent and interlaced
#$im->transparent($couleurs_allouee{'blanc'});
	$im->interlaced('true');

# Put a frame around the picture
	$im->rectangle(0, 0, $x -1, $y -1, $couleurs_allouee{$self->couleur_contour});
# Put the background color
	$im->filledRectangle(1, 1, $x -2, $y -2, $couleurs_allouee{$self->couleur_background});

# We add the word cases
	$im->filledRectangle(2, 2, $intersection - $self->distance_entre_mots, $y -3, $couleurs_allouee{$self->couleur_interne});

# make sure we are writing to a binary stream
	binmode STDOUT;

# Convert the image to PNG and print it on standard output
	print $im->png;
}

1;
