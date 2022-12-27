#include "queue.h"
#include "dll.h"
#include "music_player.h"
#include <stdio.h>
#include <stdlib.h>

playlist_t *create_playlist() // return a newly created doubly linked list
{
	// DO NOT MODIFY!!!
	playlist_t *playlist = (playlist_t *)malloc(sizeof(playlist_t));
	playlist->list = create_list();
	playlist->num_songs = 0;
	playlist->last_song = NULL;
	return playlist;
}

void delete_playlist(playlist_t *playlist) // delete the playlist
{
	// DO NOT MODIFY!!!
	delete_list(playlist->list);
	free(playlist);
}

music_queue_t *create_music_queue() // return a newly created queue
{
	// DO NOT MODIFY!!!
	return create_queue();
}

void clear_music_queue(music_queue_t *q) // clear the queue q
{
	// DO NOT MODIFY!!!
	delete_queue(q);
}

void add_song(playlist_t *playlist, int song_id, int where) // TODO: add a song id to the end of the playlist
{
	
	if (where == -2)
		insert_back(playlist->list, song_id);
	else if (where == -1)
		insert_front(playlist->list, song_id);
	else
		insert_after(playlist->list, song_id, where);
	playlist->num_songs = playlist->list->size;
}

void delete_song(playlist_t *playlist, int song_id) // TODO: remove song id from the playlist
{
	delete_node(playlist->list, song_id);
	playlist->num_songs = playlist->list->size;
}

song_t *search_song(playlist_t *playlist, int song_id) // TODO: return a pointer to the node where the song id is present in the playlist
{
	return search(playlist->list, song_id);
}

void search_and_play(playlist_t *playlist, int song_id) // TODO: play the song with given song_id from the list(no need to bother about the queue. Call to this function should always play the given song and further calls to play_next and play_previous)
{
	song_t *song = search(playlist->list, song_id);
	if (song != NULL)
		play_song(song->data);
	playlist->last_song = song;
}

void play_next(playlist_t *playlist, music_queue_t *q) // TODO: play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
{
	if (playlist->num_songs != 0)
	{
		if (q->size != 0)
			play_from_queue(q);
		else
		{
			if (playlist->last_song == NULL || playlist->last_song->next == NULL)
			{
				playlist->last_song = playlist->list->head;
			}
			else
			{
				playlist->last_song = playlist->last_song->next;
			}
			play_song(playlist->last_song->data);
		}
	}
}

void play_previous(playlist_t *playlist) // TODO: play the previous song from the linked list
{
	if (playlist->num_songs != 0)
	{
		if (playlist->last_song == NULL || playlist->last_song->prev == NULL)
		{
			playlist->last_song = playlist->list->tail;
		}
		else
		{
			playlist->last_song = playlist->last_song->prev;
		}
		play_song(playlist->last_song->data);
	}
}

void insert_to_queue(music_queue_t *q, int song_id) // TODO: insert a song id to the queue
{
	enqueue(q, song_id);
}
void play_from_queue(music_queue_t *q) // TODO: play a song from the queue
{
	int song = dequeue(q);
	if (song != -1)
		play_song(song);
}



void reverse(playlist_t *playlist) // TODO: reverse the order of the songs in the given playlist. (Swap the nodes, not data)
{
	song_t *temp = playlist->list->head;
	song_t *t;
	while (temp != NULL)
	{
		t = temp->next;
		temp->next = temp->prev;
		temp->prev = t;
		if (temp->prev == NULL)
		{
			temp = playlist->list->head;
			playlist->list->head = playlist->list->tail;
			playlist->list->tail = temp;
		}
		temp = t;
	}
}

void k_swap(playlist_t *playlist, int k) // TODO: swap the node at position i with node at position i+k upto the point where i+k is less than the size of the linked list
{
	int i, j = 0;
	song_t *temp = playlist->list->head;
	song_t *tempk;
	song_t *t;
	for (i = 0; (i + k) < playlist->num_songs; i++)
	{
		tempk = temp;
		j = 0;
		while (j < k)
		{
			tempk = tempk->next;
			j++;
		}
		t = temp->next;
		temp->next = tempk->next;
		if (k == 1)
			tempk->next = temp;
		else
			tempk->next = t;
		t = temp->prev;
		if (k == 1)
			temp->prev = tempk;
		else
			temp->prev = tempk->prev;
		tempk->prev = t;
		if (temp->prev != NULL)
			temp->prev->next = temp;
		if (temp->next != NULL)
			temp->next->prev = temp;
		if (tempk->next != NULL)
			tempk->next->prev = tempk;
		if (tempk->prev != NULL)
			tempk->prev->next = tempk;
		if (tempk->prev == NULL)
			playlist->list->head = tempk;
		if (temp->next == NULL)
			playlist->list->tail = temp;
		temp = tempk->next;
	}
}



song_t *debug(playlist_t *playlist) // TODO: if the given linked list has a cycle, return the start of the cycle, else return null. Check cycles only in forward direction i.e with the next pointer. No need to check for cycles in the backward pointer.
{
	return playlist->list->tail->next;
}

void display_playlist(playlist_t *p) // Displays the playlist
{
	// DO NOT MODIFY!!!
	display_list(p->list);
}

void play_song(int song_id)
{
	// DO NOT MODIFY!!!
	printf("Playing: %d\n", song_id);
}

void shuffle(playlist_t *playlist, int k) // TODO: perform k_swap and reverse
{
	k_swap(playlist, k);
	reverse(playlist);
}