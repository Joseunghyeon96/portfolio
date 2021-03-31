using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StoneMonster : MonoBehaviour
{    
    void Update()
    {
        if (GameObject.Find("DataController").GetComponent<DataController>().Get_curStage() == 3 &&
            GameObject.Find("UIController").GetComponent<UIController>().bossStageStart)
            return;

        if (!GameObject.Find("UIController").GetComponent<UIController>().clear)
        this.transform.Translate(Vector3.forward * 2.5f * Time.deltaTime);
    }
}
