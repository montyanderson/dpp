#include "dpp.h"
#define S 8
#define D 9

char str[782];

void setup() {
    strcpy(str, "Welcome, dear Rosencrantz and Guildenstern. \
Moreover that we much did long to see you, \
The need we have to use you did provoke \
Our hasty sending. Something have you heard \
Of Hamlet’s “transformation”—so call it \
Since nor th' exterior nor the inward man \
Resembles that it was. What it should be, \
More than his father’s death, that thus hath put him \
So much from th' understanding of himself, \
I cannot dream of. I entreat you both \
That, being of so young days brought up with him \
And since so neighbored to his youth and 'havior, \
That you vouchsafe your rest here in our court \
Some little time so by your companies \
To draw him on to pleasures and to gather, \
So much as from occasion you may glean, \
Whether aught, to us unknown, afflicts him thus \
That, opened, lies within our remedy.\n");

  dpp_write(8, 9, str, strlen(str));

  
}

void loop() {
}
