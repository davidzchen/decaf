#!/usr/bin/perl

use Getopt::Std;

getopt('fe');

our($opt_f, $opt_e);

$testfile = $opt_f . ".test";
$infile   = $opt_f . "." . $opt_e;

open TEMPLATE, "<", "test.in" or die $!;
open TESTFILE, ">", $testfile or die $!;

while (my $line = <TEMPLATE>) {
	$line =~ s/\@TESTNAME\@/$opt_f/g;
	$line =~ s/\@TESTEXT\@/$opt_e/g;

	print TESTFILE $line;
}
