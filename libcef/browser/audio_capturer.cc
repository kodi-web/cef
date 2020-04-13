// Copyright (c) 2019 The Chromium Embedded Framework Authors.
// Portions copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "libcef/browser/audio_capturer.h"
#include "libcef/browser/browser_host_impl.h"

#include "components/mirroring/service/captured_audio_input.h"
#include "content/public/browser/audio_loopback_stream_creator.h"
#include "media/audio/audio_input_device.h"

namespace {
cef_channel_layout_t TranslateChannelLayout(media::ChannelLayout channel) {
  switch (channel) {
    case media::CHANNEL_LAYOUT_UNSUPPORTED:
      return CEF_CHANNEL_LAYOUT_UNSUPPORTED;
    case media::CHANNEL_LAYOUT_MONO:
      return CEF_CHANNEL_LAYOUT_MONO;
    case media::CHANNEL_LAYOUT_STEREO:
      return CEF_CHANNEL_LAYOUT_STEREO;
    case media::CHANNEL_LAYOUT_2_1:
      return CEF_CHANNEL_LAYOUT_2_1;
    case media::CHANNEL_LAYOUT_SURROUND:
      return CEF_CHANNEL_LAYOUT_SURROUND;
    case media::CHANNEL_LAYOUT_4_0:
      return CEF_CHANNEL_LAYOUT_4_0;
    case media::CHANNEL_LAYOUT_2_2:
      return CEF_CHANNEL_LAYOUT_2_2;
    case media::CHANNEL_LAYOUT_QUAD:
      return CEF_CHANNEL_LAYOUT_QUAD;
    case media::CHANNEL_LAYOUT_5_0:
      return CEF_CHANNEL_LAYOUT_5_0;
    case media::CHANNEL_LAYOUT_5_1:
      return CEF_CHANNEL_LAYOUT_5_1;
    case media::CHANNEL_LAYOUT_5_0_BACK:
      return CEF_CHANNEL_LAYOUT_5_0_BACK;
    case media::CHANNEL_LAYOUT_5_1_BACK:
      return CEF_CHANNEL_LAYOUT_5_1_BACK;
    case media::CHANNEL_LAYOUT_7_0:
      return CEF_CHANNEL_LAYOUT_7_0;
    case media::CHANNEL_LAYOUT_7_1:
      return CEF_CHANNEL_LAYOUT_7_1;
    case media::CHANNEL_LAYOUT_7_1_WIDE:
      return CEF_CHANNEL_LAYOUT_7_1_WIDE;
    case media::CHANNEL_LAYOUT_STEREO_DOWNMIX:
      return CEF_CHANNEL_LAYOUT_STEREO_DOWNMIX;
    case media::CHANNEL_LAYOUT_2POINT1:
      return CEF_CHANNEL_LAYOUT_2POINT1;
    case media::CHANNEL_LAYOUT_3_1:
      return CEF_CHANNEL_LAYOUT_3_1;
    case media::CHANNEL_LAYOUT_4_1:
      return CEF_CHANNEL_LAYOUT_4_1;
    case media::CHANNEL_LAYOUT_6_0:
      return CEF_CHANNEL_LAYOUT_6_0;
    case media::CHANNEL_LAYOUT_6_0_FRONT:
      return CEF_CHANNEL_LAYOUT_6_0_FRONT;
    case media::CHANNEL_LAYOUT_HEXAGONAL:
      return CEF_CHANNEL_LAYOUT_HEXAGONAL;
    case media::CHANNEL_LAYOUT_6_1:
      return CEF_CHANNEL_LAYOUT_6_1;
    case media::CHANNEL_LAYOUT_6_1_BACK:
      return CEF_CHANNEL_LAYOUT_6_1_BACK;
    case media::CHANNEL_LAYOUT_6_1_FRONT:
      return CEF_CHANNEL_LAYOUT_6_1_FRONT;
    case media::CHANNEL_LAYOUT_7_0_FRONT:
      return CEF_CHANNEL_LAYOUT_7_0_FRONT;
    case media::CHANNEL_LAYOUT_7_1_WIDE_BACK:
      return CEF_CHANNEL_LAYOUT_7_1_WIDE_BACK;
    case media::CHANNEL_LAYOUT_OCTAGONAL:
      return CEF_CHANNEL_LAYOUT_OCTAGONAL;
    case media::CHANNEL_LAYOUT_DISCRETE:
      return CEF_CHANNEL_LAYOUT_DISCRETE;
    case media::CHANNEL_LAYOUT_STEREO_AND_KEYBOARD_MIC:
      return CEF_CHANNEL_LAYOUT_STEREO_AND_KEYBOARD_MIC;
    case media::CHANNEL_LAYOUT_4_1_QUAD_SIDE:
      return CEF_CHANNEL_LAYOUT_4_1_QUAD_SIDE;
    case media::CHANNEL_LAYOUT_BITSTREAM:
      return CEF_CHANNEL_LAYOUT_BITSTREAM;
    case media::CHANNEL_LAYOUT_NONE:
      return CEF_CHANNEL_LAYOUT_NONE;
  }
  return CEF_CHANNEL_LAYOUT_NONE;
}

media::ChannelLayout TranslateCefChannelLayout(cef_channel_layout_t channel) {
  switch (channel) {
    case CEF_CHANNEL_LAYOUT_UNSUPPORTED:
      return media::CHANNEL_LAYOUT_UNSUPPORTED;
    case CEF_CHANNEL_LAYOUT_MONO:
      return media::CHANNEL_LAYOUT_MONO;
    case CEF_CHANNEL_LAYOUT_STEREO:
      return media::CHANNEL_LAYOUT_STEREO;
    case CEF_CHANNEL_LAYOUT_2_1:
      return media::CHANNEL_LAYOUT_2_1;
    case CEF_CHANNEL_LAYOUT_SURROUND:
      return media::CHANNEL_LAYOUT_SURROUND;
    case CEF_CHANNEL_LAYOUT_4_0:
      return media::CHANNEL_LAYOUT_4_0;
    case CEF_CHANNEL_LAYOUT_2_2:
      return media::CHANNEL_LAYOUT_2_2;
    case CEF_CHANNEL_LAYOUT_QUAD:
      return media::CHANNEL_LAYOUT_QUAD;
    case CEF_CHANNEL_LAYOUT_5_0:
      return media::CHANNEL_LAYOUT_5_0;
    case CEF_CHANNEL_LAYOUT_5_1:
      return media::CHANNEL_LAYOUT_5_1;
    case CEF_CHANNEL_LAYOUT_5_0_BACK:
      return media::CHANNEL_LAYOUT_5_0_BACK;
    case CEF_CHANNEL_LAYOUT_5_1_BACK:
      return media::CHANNEL_LAYOUT_5_1_BACK;
    case CEF_CHANNEL_LAYOUT_7_0:
      return media::CHANNEL_LAYOUT_7_0;
    case CEF_CHANNEL_LAYOUT_7_1:
      return media::CHANNEL_LAYOUT_7_1;
    case CEF_CHANNEL_LAYOUT_7_1_WIDE:
      return media::CHANNEL_LAYOUT_7_1_WIDE;
    case CEF_CHANNEL_LAYOUT_STEREO_DOWNMIX:
      return media::CHANNEL_LAYOUT_STEREO_DOWNMIX;
    case CEF_CHANNEL_LAYOUT_2POINT1:
      return media::CHANNEL_LAYOUT_2POINT1;
    case CEF_CHANNEL_LAYOUT_3_1:
      return media::CHANNEL_LAYOUT_3_1;
    case CEF_CHANNEL_LAYOUT_4_1:
      return media::CHANNEL_LAYOUT_4_1;
    case CEF_CHANNEL_LAYOUT_6_0:
      return media::CHANNEL_LAYOUT_6_0;
    case CEF_CHANNEL_LAYOUT_6_0_FRONT:
      return media::CHANNEL_LAYOUT_6_0_FRONT;
    case CEF_CHANNEL_LAYOUT_HEXAGONAL:
      return media::CHANNEL_LAYOUT_HEXAGONAL;
    case CEF_CHANNEL_LAYOUT_6_1:
      return media::CHANNEL_LAYOUT_6_1;
    case CEF_CHANNEL_LAYOUT_6_1_BACK:
      return media::CHANNEL_LAYOUT_6_1_BACK;
    case CEF_CHANNEL_LAYOUT_6_1_FRONT:
      return media::CHANNEL_LAYOUT_6_1_FRONT;
    case CEF_CHANNEL_LAYOUT_7_0_FRONT:
      return media::CHANNEL_LAYOUT_7_0_FRONT;
    case CEF_CHANNEL_LAYOUT_7_1_WIDE_BACK:
      return media::CHANNEL_LAYOUT_7_1_WIDE_BACK;
    case CEF_CHANNEL_LAYOUT_OCTAGONAL:
      return media::CHANNEL_LAYOUT_OCTAGONAL;
    case CEF_CHANNEL_LAYOUT_DISCRETE:
      return media::CHANNEL_LAYOUT_DISCRETE;
    case CEF_CHANNEL_LAYOUT_STEREO_AND_KEYBOARD_MIC:
      return media::CHANNEL_LAYOUT_STEREO_AND_KEYBOARD_MIC;
    case CEF_CHANNEL_LAYOUT_4_1_QUAD_SIDE:
      return media::CHANNEL_LAYOUT_4_1_QUAD_SIDE;
    case CEF_CHANNEL_LAYOUT_BITSTREAM:
      return media::CHANNEL_LAYOUT_BITSTREAM;
    case CEF_CHANNEL_LAYOUT_NONE:
      return media::CHANNEL_LAYOUT_NONE;
  }
  return media::CHANNEL_LAYOUT_NONE;
}

void StreamCreatorHelper(
    content::WebContents* source_web_contents,
    content::AudioLoopbackStreamCreator* audio_stream_creator,
    mojo::PendingRemote<mirroring::mojom::AudioStreamCreatorClient> client,
    const media::AudioParameters& params,
    uint32_t total_segments) {
  audio_stream_creator->CreateLoopbackStream(
      source_web_contents, params, total_segments,
      base::BindRepeating(
          [](mojo::PendingRemote<mirroring::mojom::AudioStreamCreatorClient>
                 client,
             mojo::PendingRemote<media::mojom::AudioInputStream> stream,
             mojo::PendingReceiver<media::mojom::AudioInputStreamClient>
                 client_receiver,
             media::mojom::ReadOnlyAudioDataPipePtr data_pipe) {
            mojo::Remote<mirroring::mojom::AudioStreamCreatorClient>
                audio_client(std::move(client));
            audio_client->StreamCreated(
                std::move(stream), std::move(client_receiver),
                std::move(data_pipe), false /* initially_muted */);
          },
          base::Passed(&client)));
}
}  // namespace

int CefAudioCapturer::audio_stream_id = 0;

CefAudioCapturer::CefAudioCapturer(const CefAudioParameters& params,
                                   CefRefPtr<CefBrowserHostImpl> browser,
                                   CefRefPtr<CefAudioHandler> audio_handler)
    : params_(media::AudioParameters::AUDIO_PCM_LINEAR,
              TranslateCefChannelLayout(params.channel_layout),
              params.sample_rate,
              params.frames_per_buffer),
      browser_(browser),
      audio_handler_(audio_handler),
      audio_stream_creator_(content::AudioLoopbackStreamCreator::
                                CreateInProcessAudioLoopbackStreamCreator()) {
  static_assert(
      static_cast<int>(CEF_CHANNEL_LAYOUT_MAX) ==
          static_cast<int>(media::CHANNEL_LAYOUT_MAX),
      "cef_channel_layout_t must match the ChannelLayout enum in Chromium");

  DCHECK(params_.IsValid());
  DCHECK(browser_);
  DCHECK(audio_handler_);
  DCHECK(browser_->web_contents());

  thread_checker_.DetachFromThread();

  audio_stream_id_ = ++audio_stream_id;
  capturer_running_ = false;
  audio_input_device_ = new media::AudioInputDevice(
      std::make_unique<mirroring::CapturedAudioInput>(base::BindRepeating(
          &StreamCreatorHelper, base::Unretained(browser_->web_contents()),
          base::Unretained(audio_stream_creator_.get()))),
      media::AudioInputDevice::kLoopback);

  audio_input_device_->Initialize(params_, this);
}

CefAudioCapturer::~CefAudioCapturer() {
  DCHECK(thread_checker_.CalledOnValidThread());

  Stop();

  browser_ = nullptr;
  audio_handler_ = nullptr;
  audio_input_device_ = nullptr;
  audio_stream_creator_.reset();
}

void CefAudioCapturer::Start() {
  DCHECK(thread_checker_.CalledOnValidThread());
  if (!capturer_running_) {
    capturer_running_ = true;
    audio_input_device_->Start();
  }
}

void CefAudioCapturer::Stop() {
  DCHECK(thread_checker_.CalledOnValidThread());
  if (capturer_running_) {
    capturer_running_ = false;
    audio_input_device_->Stop();
    audio_handler_->OnAudioStreamStopped(browser_, audio_stream_id_);
  }
}

void CefAudioCapturer::OnCaptureStarted() {
  audio_handler_->OnAudioStreamStarted(
      browser_, audio_stream_id_, params_.channels(),
      TranslateChannelLayout(params_.channel_layout()), params_.sample_rate(),
      params_.frames_per_buffer());
}

void CefAudioCapturer::Capture(const media::AudioBus* source,
                               base::TimeTicks audio_capture_time,
                               double /*volume*/,
                               bool /*key_pressed*/) {
  if (!capturer_running_)
    return;

  const int channels = source->channels();
  std::array<const float*, media::CHANNELS_MAX> data;
  DCHECK(channels <= static_cast<int>(data.size()));
  for (int c = 0; c < channels; ++c) {
    data[c] = source->channel(c);
  }
  base::TimeDelta pts = audio_capture_time - base::TimeTicks::UnixEpoch();
  audio_handler_->OnAudioStreamPacket(browser_, audio_stream_id_, data.data(), source->frames(),
                                      pts.InMilliseconds());
}

void CefAudioCapturer::OnCaptureError(const std::string& message) {
  if (capturer_running_) {
    capturer_running_ = false;
    audio_input_device_->Stop();
  }
  audio_handler_->OnAudioStreamError(browser_, audio_stream_id_, message);
}