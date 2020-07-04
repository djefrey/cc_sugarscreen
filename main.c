#include <stdio.h>
#include <string.h>

#include "game.h"

int main()
{
    t_game * g = game_init();

    game_loop(g);
    return 0;
}

/* Scoreboard: (47 characters max)
  Player/Broker
  
  14 - 21
  20 - 19
  17 - 15
  10 - 14
  16 - 20
  15 - 13
*/

void game_loop(t_game * g)
{
  int turn = 1;
  char sb[64];

  while(!is_game_finished(g)){
    printf("\n --- Turn %i ---\n\n", turn);

    //Afficher le nombre de jetons du joueur
    broker_new_hand(g);
    
    //Le croupier pioche
    player_new_hand(g);
    
    //Le joueur pioche
    print_player_hand(g->player);
    
    //Afficher la main du joueur
    broker_place_bet(g);
    
    //Le croupier mise
    player_place_bet(g);

    int inhand = player_ask_cards(g);
      
    //Le joueur mise
    int p_hand = sum_player_hand(g->player);
    /*Le joueur choisi la valeur de ses Valets et cett function "return" le score du joueur*/

    // Afficher lesscore du croupier et du joueu (le score du joueur doit êtr edonné par la variable p_hand)
    print_turn_results(g,p_hand); 

    if(inhand == 6 && p_hand < 21){
      p_hand = 21;
    }

    if(p_hand > 21){
      player_breakthrough(g); 
    
    }else if(p_hand == 21){
      player_jackpot(g);

    }else if(p_hand > g->broker){
      player_win(g);

    }else{
      player_lost(g);
    }

    char entry[12];
    sprintf(entry, "\t%d - %d\n", p_hand, g->broker);
    strcat(sb, entry);

    if(g->player->score <= 0){
      printf("You lost all your coins !");
      game_end(g);
    }else if(turn == 1){
      printf("Game over ! Your coins : %i \n", g->player->score);
      game_end(g);
    }else{
      turn++;
    }
  }

  printf("\nScoreboard:\nPlayer - Broker\n%s",sb);

  printf("\n\n ----- REMATCH ----- \n\n");

  // Rematch
  t_game * newG = game_init();

  game_loop(newG);
}