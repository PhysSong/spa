/*************************************************************************/
/* osc-plugin.cpp - a minimal OSC example plugin                         */
/* Copyright (C) 2018                                                    */
/* Johannes Lorenz (j.git$$$lorenz-ho.me, $$$=@)                         */
/*                                                                       */
/* This program is free software; you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation; either version 3 of the License, or (at */
/* your option) any later version.                                       */
/* This program is distributed in the hope that it will be useful, but   */
/* WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU      */
/* General Public License for more details.                              */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program; if not, write to the Free Software           */
/* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA  */
/*************************************************************************/

/**
	@file osc-plugin.cpp
	a simple example gain plugin
	less than 150 LOC, including license and metadata
*/

#include <cstring>
#include <iostream>
#include <vector>

#include <spa/audio.h>

class example_plugin : public spa::plugin
{
	//! ports can be extended, this is being hidden from the source
	struct buffersize_port : public spa::audio::buffersize
	{
		int some_extra_value;
		buffersize_port() : some_extra_value(0) {}
	};
	//! useless buffer, just for demonstration
	std::vector<float> out_buffer_l, out_buffer_r;

public:
	void run() override
	{
		while(osc_in.read_msg())
		{
			if(!strcmp(osc_in.path(), "/gain"))
			{
				spa::audio::assert_types_are("/gain",
					"f", osc_in.types());
				gain = osc_in.arg(0).f;
			} else {
				std::cerr << "warning: unsupported "
					"OSC string \"" << osc_in.path()
					<< "\", ignoring...";
			}
		}

		for(unsigned i = 0; i < buffersize; ++i)
		{
			out_buffer_l[i] = gain * in.left[i];
			out_buffer_r[i] = gain * in.right[i];
		}

		memcpy(out.left, out_buffer_l.data(), buffersize * sizeof(out.left[0]));
		memcpy(out.right, out_buffer_r.data(), buffersize * sizeof(out.right[0]));
	}

	void init() override {
		out_buffer_l.resize(buffersize);
		out_buffer_r.resize(buffersize);
	}

public:	// FEATURE: make these private?
	virtual ~example_plugin() {}
	example_plugin() : osc_in(1024) {}

private:

	void activate() override {}
	void deactivate() override {}

	float gain = 0.0f; // received via OSC

	spa::audio::stereo::in in;
	spa::audio::stereo::out out;
	buffersize_port buffersize;
	spa::audio::osc_ringbuffer_in osc_in;

	spa::port_ref_base& port(const char* path) override
	{
		using p = spa::port_ref_base;
		switch(path[0])
		{
			case 'i': return in;
			case 'o': return path[1] == 's' ? (p&)osc_in : (p&)out;
			case 'b': return buffersize;
			default: throw spa::port_not_found(path);
		}
	}
};

class example_descriptor : public spa::descriptor
{
	SPA_DESCRIPTOR
public:
	example_descriptor() { properties.hard_rt_capable = 1; }

	hoster_t hoster() const override { return hoster_t::github; }
	const char* organization_url() const override {
		return "JohannesLorenz"; /* TODO: create spa organisation? */ }
	const char* project_url() const override { return "spa"; }
	const char* label() const override { return "example-plugin"; }

	const char* project() const override { return "spa"; }
	const char* name() const override { return "Example Plugin"; }
	const char* authors() const override { return "Johannes Lorenz"; }

	const char* description_full() const override {
		return description_line(); }
	const char* description_line() const override {
		return "example audio gain plugin for tests"; }

	license_type license() const override { return license_type::gpl_3_0; }

	struct port_names_t { const char** names; };
	spa::simple_vec<spa::simple_str> port_names() const override {
		return { "in", "out", "buffersize", "osc" };
	}

	example_plugin* instantiate() const override {
		return new example_plugin; }
};

extern "C" {
//! the main entry point
const spa::descriptor* spa_descriptor(unsigned long )
{
	// we have only one plugin, ignore the number
	return new example_descriptor;
}
}

