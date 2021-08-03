using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TitleManager : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject GameDescription;

    void Start()
    {
        Cursor.visible = true;
        Cursor.lockState = CursorLockMode.Confined;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void LoadStartScene()
    {
        SceneManager.LoadScene("LevelSelect");
    }
    public void QuitGame()
    {
        Application.Quit();
    }
    public void VisibleGameDescription(bool _Input)
    {
        GameDescription.active = _Input;
    }

}
