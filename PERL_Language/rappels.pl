#!/usr/bin/perl -w
use strict;

sin($x) cos($x) renvoient le sinus et le cosinus de $x.
exp($x) log($x) renvoient e puissance $x et le logarithme en base e de $x.
abs($x) renvoie la valeur absolue de $x.
sqrt($x) renvoie la racine carrée de $x.

2**10 = 2 puissance 10 

length($x) #renvoie la longueur de la chaîne $x. Par exemple length("bonjour\n") vaut 8 et length('bonjour\n')
vaut 9.
chop($x)# supprime le dernier caractère de la chaîne $x (la variable $x est modifiée). Ce caractère est renvoyé par la fonction : $c = chop($l);
chomp($x) #supprime le dernier caractère de $x s'il s'agit d'une fin de ligne (la variable $x est modifiée). Cette fonction peut prendre plusieurs arguments, chacun subira un sort similaire. Ne pas écrire *incorrect*
$x=chomp($x) #*incorrect* car chomp renvoie le nombre de caractères supprimés. Cette fonction nous sera très utile lorsque nous lirons des fichiers ligne à ligne.
reverse($x) en contexte scalaire, # renvoie la chaîne composée des caractères de $x dans l'ordre inverse. Par exemple '
$v = reverse("bonjour\n") #affecte "\nruojnob" à $v. On rencontrera aussi cette fonction chez les listes (son comportement dépend du contexte).'
#Cette fonction peut être une lvalue, c'est-à-dire qu'on peut lui affecter une valeur (lvalue pour left-value : à la gauche du signe égal de l'affectation) :
my $v = "salut toi";
substr($v,5,1) = "ation à ";
substr($x,offset,length) #vaut la sous-chaîne de position offset et de longueur length. Les positions
commencent à 0 : substr("bonjour",1,2) #vaut on. La longueur peut être omise, dans ce cas toute la partie droite de la chaîne est sélectionnée.
index($chaîne,$sousChaîne,$position) #renvoie la position de la première occurrence de $sousChaîne dans $chaîne. Le troisième paramètre, s'il est fourni, indique la position du début de la recherche ; sinon la recherche part du début de la chaîne (position 0). ''
rindex($chaîne,$sousChaîne,$position) #effectue la même recherche que la fonction index mais en partant de la fin de la chaîne (la recherche est effectuée de droite à gauche).
instruction while( condition );

# Exemple
my $v ="##########";
for( my $i=9; $i>0; $i-- )
{
	print("$i impair\n")
	if( $i % 2 );
	print( "-"x$i . "\n") unless( $i % 3 );
	substr( $v, $i, 0 ) = $i;
}
print("$v\n");

@t = qw/ attention 'aux erreurs' bêtes /;

my $x = shift; # C'est comme si j'avais écrit : = shift @_;

$s = join(" ",1,2,3); #La variable $s vaut alors la chaîne "1 2 3".
$s = join(',',$x,$y,$y); #Les valeurs des trois variables sont jointes en les alternant avec des virgules. Le résultat est affecté à $s.
$s = join(" : ",@t); #La variable vaut alors la concaténation des valeurs du tableau @t avec " : " pour séparateur.

@t = split(/-/,"4-12-455"); #Le tableau comporte alors les éléments 4, 12 et 455.
($x,$y) = split(/==/,$v); #Les deux variables auront pour valeur les deux premières chaînes de caractères qui soient séparées par deux signes d'égalité.
print join(':',split(/ /,'salut ici')); #Affiche salut:ici (il existe des méthodes plus efficaces et plus lisibles de faire cela...).

$liste2 = sort( liste1 );
$liste2 = sort( { comparaison } liste1 );

@s = sort( {$a cmp $b} @t ); #La liste @s a pour valeur la liste @t triée selon l'ordre lexical.
@s = sort( @t ); #Le fonctionnement est identique à l'exemple précédent.
@s = sort( {$a <=> $b} @t ); #Le critère de tri est ici numérique.
@s = sort( {$a <=> $b or $a cmp $b} @t ); #Une expression composée peut bien sûr servir de critère : le tri est ici d'abord numérique puis lexical. Cela permet de placer '8 navets' avant '12 carottes', et '12 carottes' avant '12 navets'.
@s = sort( { fonction($a,$b) } @t ); #Vous pouvez écrire votre propre fonction de tri (à deux arguments) ; elle doit renvoyer un nombre dont la valeur dépend de l'ordre voulu (voir juste avant).

@t = grep { $_<0 } $x,$y,$z; #Affecte à @t les éléments négatifs de la liste.
@s = grep { $_!=8 and $_!=4 } @t; #Met dans @s les éléments de @t différents de 4 et de 8.

@s = map( { -$_ } @t ); #Le tableau @s aura pour valeurs les opposés des valeurs de @t.
@p = map( { $_."s" } @t ); #Tous les mots de @t sont mis au pluriel dans @p.
@s = map( { substr($_,0,2) } @t ); #Le tableau @s aura pour valeurs les deux premiers caractères des valeurs de @t.
@s = map( { fonction($_) } @t ); #Vous pouvez écrire votre propre fonction ; les valeurs qu'elle renverra seront placées dans @s.
map( { $_*=4 } @t );

if( exists( $h{hello} ) )
{
	print "La clef 'hello' existe\n";
}

my %h = ("Paul" => "01.23.45.67.89", "Virginie" => "06.06.06.06.06", "Pierre" => "heu ...");
# <=>
my %h = ("Paul", "01.23.45.67.89", "Virginie", "06.06.06.06.06", "Pierre", "heu ...");

perldoc -f -X # Pour connaître l'ensemble des opérations sur les fichiers

@l = glob('/usr/include/*.h');
# <=>
@l = </usr/include/*.h>;

foreach my $name ( <.*>, <*> )
{
	next if( ! -d $name || ! -w $name );
	print "$name : ". ( -s $name ) ."\n";
}

# Ouverture de fichiers : 
# < = lecture ; > = écriture (écrasement) ; >> = ajout ; +> = lecture + écriture (écrasement) ; +< = lecture + écriture;

# Pour supprimer une clef dans une table de hachage
delete($h{clefasupprimer});

# Variable d'environnement : %ENV


my @ensA = (1, 3, 5, 6, 7, 8);
my @ensB = (2, 3, 5, 7, 9);
my %hash = ();
# Qu'une seule table ...
foreach my $e (@ensA) { $hash{$e}++; }
foreach my $e (@ensB) { $hash{$e}++; }
my @union = sort( {$a<=>$b} keys(%hash) );
my @inter = sort( {$a<=>$b} ( grep { $hash{$_}==2 } keys(%hash) ));
print("@union\n");
# affiche : 1 2 3 5 6 7 8 9
print("@inter\n");
# affiche : 3 5 7

# Après ouverture d'un fichier : 
# $l = <FIC>; Lit une ligne
# @t = <FIC>; lit toutes les lignes

Ouvrir des fichiers : 
open(FIC , "ls");

Ouvrir un fichier en changeant sa sortie standard :
open(FIC , "ls |");

Ouvrir un fichier en changeant son entrée standard :
open(FIC , "| cat");

Les fichiers DBM
Script de création:
my %h;
dbmopen(%h,"data",0644) or die($!);
$h{'prenom'} = 'Larry';
dbmclose(%h) or die($!);

Script d''utilisation :
my %h;
dbmopen(%h,"data",0644) or die($!);
print "$h{'prenom'}\n";
dbmclose(%h) or die($!);

Expressions régulières
Pattern matching (Correspondance) et Substitution

^ en début de [^quelque-chose] veut dire PAS quelque-chose
[aeiouy] = une de ces lettres
[2a-z0] = soit une lettre minuscule, soit 2 soit 0

Quantificateurs
* = 0 à n fois ; + = 1 ou n fois ; ? = 0 ou 1 fois ; {n} = n fois exactement ; {n,} = n fois au moins ; {,n} = au plus n fois ; {n, z} = entre n et z;

Ensembles
\d = [0-9] (digit)
\D inverse de \d
\w alphanumérique = [0-9a-zA-Z]
\W inverse de \w
\s espacement comme [\n\t\r\f]
\S inverse de \s

Regroupement
m/(meuh){3}/

Alternatives
m/Fred|Paul|Julie Martin/
!=
m/(Fred|Paul|Julie) Martin/

#m/(.*) (?:et )+(.*) avec \1 \2/ matchera par exemple les valeurs suivantes : "Paul et Julie avec Paul Julie" et "lala et et lili avec lala lili"

if( ($x,$y) = ( $v =~ m/^(A+).*(B+)$/ ) )
{}
$x reçoit une suite de A et $y reçoit une suite de B si $v est effectivement matché

Quantificateurs gourmands et non-gourmands
* gourmand *? non
+			+?
?			??
{n,m}		{n,m}?

se souvenir de /START.*?STOP/

placer une variable dans un motif :
utiliser quotemeta
$v2 = quotemeta($v1);

un peu de translittération
$s = "azerty";
$s =~ tr/abcde/01234/;
print "$s\n"; # affiche 0z4rty

seul usage courant de tr
$s =~ tr/a-z/A-Z/;

Références 
$refv = \$v;

$$refv est équivalent à $v

références sur tableau
t = $reft
@t = @$reft
$t[i] = $$reft[i]
$t[i] = $reft->[i]

Contrer l''aplatissement des listes 
my @t1 = ( 16, -33 );
my @t2 = ( "el", 0.3, 4 );
my @t = ( 6, \@t1, \@t2, "s" );

my %h = ("truc" => "machin");
my $refh = \%h;
foreach my $k (keys %$refh)
{
	print "$k $refh->{$k}\n";
}

foreach my $p (@$r)
{
	if( ref($p) eq "ARRAY" )
	{
		print "( ";
		foreach my $v (@$p)
		{ print "$v "; }
		print ")\n";
	}
	elsif( ref($p) eq "HASH" )
	{
		foreach my $k (keys(%$p))
		{ print "$k : $p->{$k}\n"; }
	}
	elsif( !ref($p) )
	{
		print "$p\n";
	}
}

références 
my $r = ["truc","bidule"];  = référence anonyme sur tableau
my $r = {"truc" => "bidule"} = référence anonyme sur hash

pour libérer la mémoire 
$r = undef;

Référence sur fichier
open(FILE,">toto") or die("$!");
my $reff = \*FILE;
print $reff "ok\n";
sub affiche
{
	my ($ref) = @_;
	print $ref "ok\n";
}
affiche( $reff );
affiche( \*FILE ); # équivalent
close( $reff );

Référence sur fonction
sub affcoucou
{
	my ($p) = @_;
	print "Coucou $p\n";
}
my $ref = \&affcoucou;

&$ref("Larry"); # appel
$ref->("Larry"); # équivalent
sub f
{
	my ($f,$p) = @_;
	$f->( $p );
}
f( $ref, "Larry" );
f( \&affcoucou, "Larry" ); # équivalent

MODULES

utilisation
use nomdu::module;

écriture d_un module : se finit toujours par .pm comme Truc/Utils.pm

package Utils;
use strict;
use Exporter;
our @ISA = qw(Exporter);
our @EXPORT = qw(&bonjour $var);
our @EXPORT_OK = qw(&gutenTag &ciao $var2);

Les exports dans %EXPORT_TAGS doivent être dans @EXPORT ou @EXPORT_OK
our %EXPORT_TAGS=(T1=>[qw(&ciao &gutenTag)],
		T2=>[qw(&ciao $var2)]);


our $var;
sub bonjour
{
	my ($prenom) = @_;
	print "Bonjour $prenom\n";
}
1;

utilisation

use strict;

use Truc::Utils;
Truc::Utils::bonjour( "Paul" );

OU 
avec export par défaut
use Utils;
bonjour("coucou");
OU 
avec export individuel + export par défaut
use Utils qw(:DEFAULT &ciao $var2);
ciao("coucou");

OU
avec export par tag
use Utils qw(:DEFAULT &ciao :T2 );


