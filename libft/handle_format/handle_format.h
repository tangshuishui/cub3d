/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:00:35 by yshi              #+#    #+#             */
/*   Updated: 2025/06/03 14:34:49 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_FORMAT_H
# define HANDLE_FORMAT_H

int	handle_char(int ch);
int	handle_str(char *str);
int	handle_ptr(void *ptr);
int	handle_dec(int n);
int	handle_udec(unsigned int n);
int	handle_hex_l(int n);
int	handle_hex_u(int n);
int	handle_pct(void);

#endif
