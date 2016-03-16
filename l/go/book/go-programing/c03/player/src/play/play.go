package mp

import "fmt"

type Player interface {
    Play(source string)
}

func Play(source, mtype string) {
    var p Player
    fmt.Printf("type:[%s], len[%d]", mtype, len(mtype))

    switch mtype {
    case "MP3", "mp3":
        p = &MP3Player{}
        fmt.Println("MP3 Player created")
    case "WAV", "wav":
        p = &WAVPlayer{}
    default:
        fmt.Println("Unsupported music type", mtype)
        return
    }

    p.Play(source)
}