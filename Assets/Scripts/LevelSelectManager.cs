using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LevelSelectManager : MonoBehaviour
{
    public GameObject EasySelector;
    public GameObject NormalSelector;
    public GameObject HardSelector;
    public GameObject ExpertSelector;
    // Start is called before the first frame update
    void Start()
    {
        Cursor.visible = true;
        Cursor.lockState = CursorLockMode.Confined;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void LoadEasyScene()
    {
        SceneManager.LoadScene("Easy");
    }
    public void LoadEasy2Scene()
    {
        SceneManager.LoadScene("Easy2");
    }
    public void LoadNormalScene()
    {
        SceneManager.LoadScene("Normal");
    }
    public void LoadHardScene()
    {
        SceneManager.LoadScene("Hard1");
    }
    public void LoadExpertScene()
    {
        SceneManager.LoadScene("Expert");
    }

    public void VisibleEasySelector(bool _Input)
    {
        EasySelector.active = _Input;
    }
    public void VisibleNormalSelector(bool _Input)
    {
        NormalSelector.active = _Input;
    }
    public void VisibleHardSlector(bool _Input)
    {
        HardSelector.active = _Input;
    }
    public void VisibleExpertSelector(bool _Input)
    {
        ExpertSelector.active = _Input;
    }
}
