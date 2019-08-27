<?php

class sbadmin2_inputgroup
{
    protected $element;

    protected $is_valid = [
        'has_form_control' => false,
        'has_other' => false,
    ];

    protected $current_bag_type;

    protected $bag = [];

    protected $x = 0;

    public static function factory($element)
    {
        return (new static($element))->process()->getElement();
    }

    public function __construct($element) {
        $this->element = $element;
    }

    /**
     *
     */
    public static function arrayKeyFirst($array)
    {
        foreach ($array as $key => $value) { return $key; }
    }

    public function process()
    {
        $element = $this->element;
        foreach (element_children($this->element, true) as $child_name) {
            $this->processChildren($child_name, $this->element[$child_name]);
        }
        $this->populatePseudoElement();
        return $this;
    }

    /**
     *
     */
    public function getElement()
    {
        return $this->element;
    }

    /**
     *
     */
    protected function processChildren($name, $element)
    {
        if (isset($element['#sbadmin2']) && $element['#sbadmin2'] === false) {
            return;
        }
        if (isset($element['#access']) && $element['#access'] === false) {
            return;
        }
        $type = isset($element['#type']) ? $element['#type'] : (isset($element['#theme']) ? $element['#theme'] : null);
        switch ($type) {
            case 'file':
            case 'textfield':
            case 'textfield2':
            case 'textfield3':
                $this->addToBag('form_control', $name);
                break;

            case 'submit':
            case 'submit2':
            case 'submit3':
            case 'button':
            case 'link':
            case 'actions':
                $this->addToBag('button', $name);
                break;

            case 'icon':
                $this->addToBag('addon', $name);
                break;

        }
        // return $this;
    }

    /**
     *
     */
    protected function addToBag($type, $element_name)
    {
        if (null === $this->current_bag_type) {
            $this->current_bag_type = $type;
        }
        elseif ($this->current_bag_type != $type) {
            $this->current_bag_type = $type;
            $this->x++;
        }
        $this->bag[$this->x][$this->current_bag_type][] = $element_name;
        switch ($type) {
            case 'button':
            case 'addon':
                $this->is_valid['has_other'] = true;
                break;

            case 'form_control':
                $this->is_valid['has_form_control'] = true;
                break;
        }
    }

    /**
     *
     */
    protected function populatePseudoElement()
    {
        // Minimal harus ada satu form control dan salah satu dari button
        // atau addon.
        if (in_array(false, $this->is_valid)) {
            return;
        }
        $this->element['element_group'] = [
            '#theme_wrappers' => ['input_group'],
        ];
        foreach ($this->bag as $i => $group) {
            $key = $this->arrayKeyFirst($group);
            switch ($key) {
                case 'button':
                    $this->element['element_group'][$i] = ['#theme_wrappers' => ['input_group_button']];
                case 'form_control':
                    while($element_name = array_shift($group[$key])){
                        // hapus
                        sbadmin2_utils::remove_theme_wrappers('form_element', $this->element[$element_name]);
                        sbadmin2_utils::remove_theme_wrappers('container', $this->element[$element_name]);
                        $this->element['element_group'][$i][$element_name] = $this->element[$element_name];
                        $this->element[$element_name]['#printed'] = true;
                    }
                    break;

                case 'addon':
                    while($element_name = array_shift($group[$key])){
                        $this->element['element_group'][$i][$element_name] = $this->element[$element_name];
                        $this->element['element_group'][$i][$element_name]['#theme_wrappers'][] = 'input_group_addon';
                        $this->element[$element_name]['#printed'] = true;
                    }
                    break;
            }
        }

    }
}
