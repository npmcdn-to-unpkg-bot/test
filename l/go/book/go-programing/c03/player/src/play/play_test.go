package mp

import "testing"

func TestPlay(t *testing.T) {
    fakeSource := "Bear family"
    Play(fakeSource, "MP3")
    Play(fakeSource, "WAV")
}