(function () {


  function process_score() {
  }
  
  async function fetch_score(url) {
    const res = await fetch(url, {redirect: 'error'})
    const html = await res.text()
    const parser = new DOMParser()
    let dom = parser.parseFromString(html, 'text/html')
    if (!dom) {
      return
    }
    const scores = dom.querySelectorAll('.main_wrapper.t_c .m_15').forEach((score) => {
      if (score.classList.contains('w_450') && score.classList.contains('m_15') &&
          score.classList.contains('p_r') && score.classList.contains('f_0'))
      {
        const achievement = parseFloat(score.querySelectorAll('.music_score_block')[0].innerText)

        let song_name;
        let chart_type;


      } else if (score.classList.contains('screw_block')) {

      }
    })
    
    function process_score() {
      
    }
  }

  function write_to_comment(text) {
    const profile_comment = document.querySelector('.comment_block.f_l.f_12')
    const success_message = document.createElement('span')
    success_message.className = 'f_16'
    success_message.style.color = '#0A6430'
    success_message.innerHTML = text + '\n'
    profile_comment.insertAdjacentElement('beforeend', success_message)
    return
  }
  
  function main() {
    for (let i=0; i<5; i++) {
      fetch_score('/maimai-mobile/record/musicGenre/search/?genre=99&diff=' + i.toString())
    }
  }

  main()
})()