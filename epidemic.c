#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
	/* -1 - dead, 0 - healthy, any other
	   number is the day when the perason
	   got sick */
	short  *population;
	/* population size */
	long    psize = 100000;
	/* each person can make up to this
	   number of contacts per day */
	short   contacts = 5;
	/* the number of days a person stays
	   sick and contagious after the infection */
	short   duration = 14;
	/* transmissivity rate in percents */
	short   transmit = 20;
	/* mortality rate in percents */
	short   mortality = 5;
	/* the number of sick people on day 1 */
	long    sick = 1;
	long    immune = 0;
	long    dead = 0;
	long    healthy = psize - dead - sick - immune;
	long    i, j, n, m, day;
	int     print_daily = 0;

	if( NULL == ( population = calloc( psize, sizeof( short )))) {
		fprintf( stderr, "calloc(): %d\n", errno );
		return -1;
	}

	srand( time( NULL ));

	/*
	 * Randomly infect a number of people
	 * on the day one and start the model
	 * from day two.
	 */
	for( i = 0; i < sick; i++ )
		population[ rand() % psize ]++;

	/*
	 * Infection may keep spreading while there
	 * are some uninfected and contagious people.
	 */
	for( day = 2; sick > 0; day++ ) {
		for( i = 0; i < psize; i++ ) {
			/* look only at the infected people */
			if( 0 < population[ i ] ) {
				/*
				 * Let's assume that on a certain day
				 * a person may either die or develop
				 * immunity (recover).
				 */
				if( duration == ( day - population[ i ] )) {
					sick--;

					if(( rand() % 100 ) < mortality ) {
						population[ i ] = -1;
						dead++;
					}
					else {
						immune++;
					}
				}
				else if( healthy > 0 &&
						day > population[ i ] &&
						duration > ( day - population[ i ] )) {
					/*
					 * Sick people are contagious until recovery.
					 *
					 * People are not contagious on the day they
					 * got infected.
					 *
					 * Each person may contact from 0 to "contact"
					 * people.
					 */
					n = rand() % contacts;

					for( j = 0; j < n; j++ ) {
						/*
						 * rand() is guarantied to return up
						 * to 32767. For larger population
						 * simply multiply it.
						 */
						m = rand() * rand() % psize;

						/* only healthy people may get infected */
						if( ! population[ m ] ) {
							/* probability of the transmission */
							if(( rand() % 100 ) < transmit ) {
								population[ m ] = day;
								sick++;
							}
						}
					}
				}
			}
		}

		healthy = psize - sick - immune - dead;

		if( print_daily ) {
			printf( "\014\n" );
			printf( "day:      %ld\n", day );
			printf( "healthy:  %ld (%.1f%%)\n", healthy, healthy * 100. / psize );
			printf( "sick:     %ld (%.1f%%)\n", sick, sick * 100. / psize );
			printf( "immune:   %ld (%.1f%%)\n", immune, immune * 100. / psize );
			printf( "dead:     %ld (%.1f%%)\n", dead, dead * 100. / psize );
			fflush( stdout );

			delay( 200 );
		}
	}

	free( population );

	if( ! print_daily ) {
		printf( "day:      %ld\n", day );
		printf( "healthy:  %ld (%.1f%%)\n", healthy, healthy * 100. / psize );
		printf( "immune:   %ld (%.1f%%)\n", immune, immune * 100. / psize );
		printf( "dead:     %ld (%.1f%%)\n", dead, dead * 100. / psize );
	}

	return 0;
}
