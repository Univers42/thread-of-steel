/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 15:04:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "fdf_internal.h"

/* ************************************************************************** */
/*                          HIGH-PERFORMANCE PARSER                          */
/* ************************************************************************** */

// Fast integer parsing (optimized for map files)
int fast_atoi(const char *str, const char **end_ptr);
int fast_atoi_hex(const char *str, const char **end_ptr);

// Memory-mapped file parsing for large maps
typedef struct s_mmap_parser
{
    void    *mapped_memory;
    size_t  file_size;
    char    *current_pos;
    char    *end_pos;
    int     line_number;
} t_mmap_parser;

int mmap_parser_init(t_mmap_parser *parser, const char *filename);
int mmap_parser_read_line(t_mmap_parser *parser, char **line, size_t *length);
void mmap_parser_cleanup(t_mmap_parser *parser);

// Streaming parser for very large files
typedef struct s_stream_parser
{
    int     fd;
    char    *buffer;
    size_t  buffer_size;
    size_t  buffer_pos;
    size_t  bytes_in_buffer;
    int     eof_reached;
} t_stream_parser;

int stream_parser_init(t_stream_parser *parser, const char *filename, size_t buffer_size);
int stream_parser_read_chunk(t_stream_parser *parser);
void stream_parser_cleanup(t_stream_parser *parser);

/* ************************************************************************** */
/*                          VALIDATION & ERROR HANDLING                      */
/* ************************************************************************** */

// Advanced validation
typedef enum e_parse_error
{
    PARSE_OK = 0,
    PARSE_ERROR_FILE_NOT_FOUND,
    PARSE_ERROR_INVALID_FORMAT,
    PARSE_ERROR_MEMORY_ALLOCATION,
    PARSE_ERROR_TOO_LARGE,
    PARSE_ERROR_INCONSISTENT_WIDTH
} t_parse_error;

t_parse_error validate_map_file(const char *filename);
const char *parse_error_string(t_parse_error error);

#endif
